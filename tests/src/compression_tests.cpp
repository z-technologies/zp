#include "ztech/zp/compress/compression_algorithm.hpp"
#include "ztech/zp/compress/lz4.hpp"
#include "ztech/zp/compress/zstd.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "zstd.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace {

template <typename TAlgorithm,
          std::size_t                               test_length,
          ztech::zp::compress::compression_strength strength>
requires std::is_base_of_v<ztech::zp::compress::compression_algorithm,
                           TAlgorithm>
void test_compress_decompress() {
    using ztech::zp::tests::util::random_vector;

    TAlgorithm algorithm{strength};

    const auto test_vec   = random_vector<std::uint8_t, test_length>();
    const auto compressed = algorithm.compress(test_vec);

    EXPECT_NE(compressed.size(), test_vec.size());

    const auto decompressed = algorithm.decompress(compressed);

    EXPECT_EQ(test_vec.size(), decompressed.size());
    EXPECT_TRUE(std::equal(std::cbegin(test_vec),
                           std::cend(test_vec),
                           std::cbegin(decompressed),
                           std::cend(decompressed)));
}

template <typename TAlgorithm, std::size_t test_length = 0xFF>
void test_algorithm() {
    using ztech::zp::compress::compression_strength;

    ::test_compress_decompress<TAlgorithm,
                               test_length,
                               compression_strength::lowest>();
    ::test_compress_decompress<TAlgorithm,
                               test_length,
                               compression_strength::low>();
    ::test_compress_decompress<TAlgorithm,
                               test_length,
                               compression_strength::medium>();
    ::test_compress_decompress<TAlgorithm,
                               test_length,
                               compression_strength::high>();
    ::test_compress_decompress<TAlgorithm,
                               test_length,
                               compression_strength::highest>();
}

} // namespace

namespace ztech::zp::tests {

TEST(CompressionzTests, ZSTDTest) { // !NOLINT
    ::test_algorithm<ztech::zp::compress::compression_zstd>();
}

TEST(CompressionzTests, LZ4Test) { // !NOLINT
    ::test_algorithm<ztech::zp::compress::compression_lz4>();
}

} // namespace ztech::zp::tests
