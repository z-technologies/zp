#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "gtest/gtest.h"

#include <array>
#include <cstdint>
#include <cstring>

#include <iomanip>
#include <iostream>

namespace {

constexpr std::size_t header_size{ztech::zp::v1::message_header::size};

constexpr auto
calculate_checksum(const std::array<std::uint8_t, ::header_size - 1>& buf)
    -> std::uint8_t {
    std::uint8_t ret{};

    for (const auto& byte : buf) {
        ret += byte;
    }

    return ~ret;
}

} // namespace

namespace ztech::zp::tests {

TEST(MessageHeaderTests, HeaderChecksumTest) { // !NOLINT
    constexpr std::array<std::uint8_t, ::header_size - 1> test_header_bytes{
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    constexpr std::uint8_t test_header_checksum{
        ::calculate_checksum(test_header_bytes)};

    ztech::zp::v1::message_header test_header{
        .version     = 0x01,
        .type        = 0x2345,
        .command     = 0x6789,
        .flags       = static_cast<ztech::zp::v1::flags>(0xABCD),
        .tag         = 0xEF112233,
        .body_length = 0x44556677};
    test_header.update_checksum();

    EXPECT_EQ(test_header_checksum, test_header.header_checksum);
}

TEST(MessageHeaderTests, HeaderEncodeTest) { // !NOLINT
    constexpr std::array<std::uint8_t, ::header_size - 1> test_header_bytes{
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    constexpr std::uint8_t test_header_checksum{
        ::calculate_checksum(test_header_bytes)};

    ztech::zp::v1::message_header test_header{
        .version     = 0x01,
        .type        = 0x2345,
        .command     = 0x6789,
        .flags       = static_cast<ztech::zp::v1::flags>(0xABCD),
        .tag         = 0xEF112233,
        .body_length = 0x44556677};

    std::array<std::uint8_t, ::header_size> buf{};
    test_header.encode(buf);

    EXPECT_EQ(0, std::memcmp(test_header_bytes.data(), buf.data(),
                             ::header_size - 1));
    EXPECT_EQ(test_header_checksum, buf[::header_size - 1]);
}

} // namespace ztech::zp::tests
