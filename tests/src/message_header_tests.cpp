#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "gtest/gtest.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

#include <iomanip>
#include <iostream>

namespace {

constexpr std::size_t header_size{ztech::zp::message_header::size};
constexpr std::array<std::uint8_t, ::header_size> test_header_bytes{
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE};

const ztech::zp::message_header test_header{
    .type        = 0x1122,
    .command     = 0x3344,
    .flags       = static_cast<ztech::zp::flags>(0x5566),
    .tag         = 0x778899AA,
    .body_length = 0xBBCCDDEE};

template <typename T, typename U>
auto compare_containers(const T& c1, const U& c2) -> bool {
    return std::memcmp(c1.data(), c2.data(), c1.size()) == 0;
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

} // namespace ztech::zp::tests
