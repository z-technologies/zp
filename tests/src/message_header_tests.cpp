#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "gtest/gtest.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

namespace {

constexpr std::size_t header_size{ztech::zp::message_header::size};
constexpr std::array<std::uint8_t, ::header_size> test_header_bytes{
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC};

const ztech::zp::message_header test_header{.type        = 0x1122,
                                            .extra       = 0x3344,
                                            .tag         = 0x55667788,
                                            .body_length = 0x99AABBCC};

template <typename T, typename U>
auto compare_containers(const T& c1, const U& c2) -> bool {
    return std::equal(std::cbegin(c1), std::cend(c1), std::cbegin(c2),
                      std::cend(c2));
}

} // namespace

namespace ztech::zp::tests {

TEST(MessageHeaderTests, HeaderArrayEncodeTest) { // !NOLINT
    std::array<std::uint8_t, header_size> buf{};
    test_header.encode(buf);

    EXPECT_TRUE(::compare_containers(test_header_bytes, buf));
}

TEST(MessageHeaderTests, HeaderVectorEncodeTest) { // !NOLINT
    std::vector<std::uint8_t> buf{};
    test_header.encode(buf);

    EXPECT_TRUE(::compare_containers(test_header_bytes, buf));
}

TEST(MessageHeaderTests, HeaderArrayDecodeTest) { // !NOLINT
    ztech::zp::message_header header{};
    header.decode(test_header_bytes);

    EXPECT_EQ(header.type, test_header.type);
    EXPECT_EQ(header.extra, test_header.extra);
    EXPECT_EQ(header.tag, test_header.tag);
    EXPECT_EQ(header.body_length, test_header.body_length);
}

TEST(MessageHeaderTests, HeaderVectorDecodeTest) { // !NOLINT
    std::vector<std::uint8_t> buf{};
    std::copy(std::cbegin(test_header_bytes), std::cend(test_header_bytes),
              std::back_inserter<>(buf));

    ztech::zp::message_header header{};
    header.decode(test_header_bytes);

    EXPECT_EQ(header.type, test_header.type);
    EXPECT_EQ(header.extra, test_header.extra);
    EXPECT_EQ(header.tag, test_header.tag);
    EXPECT_EQ(header.body_length, test_header.body_length);
}

} // namespace ztech::zp::tests
