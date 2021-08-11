#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "gtest/gtest.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace {

constexpr std::size_t header_size{ztech::zp::message_header::size};
constexpr std::array<std::uint8_t, ::header_size> test_header_bytes{
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD};

const ztech::zp::message_header test_header{.version     = 0x11,
                                            .type        = 0x2233,
                                            .command     = 0x4455,
                                            .tag         = 0x66778899,
                                            .body_length = 0xAABBCCDD};

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

} // namespace ztech::zp::tests
