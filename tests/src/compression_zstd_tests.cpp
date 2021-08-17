#include "ztech/zp/compress/zstd.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "zstd.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace {

template <std::size_t                               test_length,
          ztech::zp::compress::compression_strength strength>
void test_zstd_compress_decompress() {
    using ztech::zp::tests::util::random_vector;

    ztech::zp::compress::compression_zstd zstd{strength};

    const auto test_vec   = random_vector<std::uint8_t, test_length>();
    const auto compressed = zstd.compress(test_vec);

    EXPECT_NE(compressed.size(), test_vec.size());

    const auto decompressed = zstd.decompress(compressed);

    EXPECT_EQ(test_vec.size(), decompressed.size());
    EXPECT_TRUE(std::equal(std::cbegin(test_vec), std::cend(test_vec),
                           std::cbegin(decompressed), std::cend(decompressed)));
}

} // namespace

namespace ztech::zp::tests {

TEST(CompressionzZSTDTests, CompressDecompressTest) { // !NOLINT
    using ztech::zp::compress::compression_strength;

    constexpr std::size_t test_length{0xFF};

    ::test_zstd_compress_decompress<test_length,
                                    compression_strength::lowest>();
    ::test_zstd_compress_decompress<test_length, compression_strength::low>();
    ::test_zstd_compress_decompress<test_length,
                                    compression_strength::medium>();
    ::test_zstd_compress_decompress<test_length, compression_strength::high>();
    ::test_zstd_compress_decompress<test_length,
                                    compression_strength::highest>();
}

} // namespace ztech::zp::tests
