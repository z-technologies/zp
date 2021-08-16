#include "ztech/zp/detail/encoding.hpp"
#include "ztech/zp/tests/util/random.hpp"

#include "gtest/gtest.h"

#include <array>
#include <cstdint>
#include <type_traits>
#include <vector>

using ztech::zp::detail::append_uint;
using ztech::zp::detail::decode_uint;
using ztech::zp::detail::get_nth_byte;
using ztech::zp::detail::write_uint;
using ztech::zp::tests::util::random;

namespace ztech::zp::tests {

TEST(EncodingTests, GetNthByteTests) { // !NOLINT
    const std::uint8_t  u8_value{random<std::uint8_t>()};
    const std::uint16_t u16_value{random<std::uint16_t>()};
    const std::uint32_t u32_value{random<std::uint32_t>()};
    const std::uint64_t u64_value{random<std::uint64_t>()};

    const auto test_type = []<typename T>(T value) {
        T tmp{value};

        for (std::size_t i{0}; i < sizeof(T); ++i) {
            EXPECT_EQ(get_nth_byte(value, sizeof(T) - i - 1), tmp & 0xFFU);

            if constexpr (sizeof(T) > 1) {
                tmp >>= 8U;
            }
        }
    };

    test_type(u8_value);
    test_type(u16_value);
    test_type(u32_value);
    test_type(u64_value);
}

TEST(EncodingTests, WriteUIntTest) { // !NOLINT
    constexpr std::array<std::uint8_t, 15> test_array{
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

    std::decay_t<decltype(test_array)> out_array{};

    write_uint<0>(static_cast<std::uint8_t>(0x11), out_array);
    write_uint<1>(static_cast<std::uint16_t>(0x2233), out_array);
    write_uint<3>(static_cast<std::uint32_t>(0x44556677), out_array);
    write_uint<7>(static_cast<std::uint64_t>(0x8899AABBCCDDEEFF), out_array);

    ASSERT_EQ(
        0, std::memcmp(test_array.data(), out_array.data(), test_array.size()));
}

TEST(EncodingTests, AppendUIntTest) { // !NOLINT
    std::vector<std::uint8_t> test_buf{0x11, 0x22, 0x33, 0x44, 0x55,
                                       0x66, 0x77, 0x88, 0x99, 0xAA,
                                       0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

    std::decay_t<decltype(test_buf)> out_buf{};

    append_uint(static_cast<std::uint8_t>(0x11), out_buf);
    append_uint(static_cast<std::uint16_t>(0x2233), out_buf);
    append_uint(static_cast<std::uint32_t>(0x44556677), out_buf);
    append_uint(static_cast<std::uint64_t>(0x8899AABBCCDDEEFF), out_buf);

    ASSERT_EQ(0, std::memcmp(test_buf.data(), out_buf.data(), test_buf.size()));
}

TEST(EncodingTests, DecodeUIntArrayTest) { // !NOLINT
    const std::uint8_t  u8_value{random<std::uint8_t>()};
    const std::uint16_t u16_value{random<std::uint16_t>()};
    const std::uint32_t u32_value{random<std::uint32_t>()};
    const std::uint64_t u64_value{random<std::uint64_t>()};

    constexpr auto u8_offset  = 0UL;
    constexpr auto u16_offset = u8_offset + sizeof(u8_value);
    constexpr auto u32_offset = u16_offset + sizeof(u16_value);
    constexpr auto u64_offset = u32_offset + sizeof(u32_value);
    constexpr auto buf_size   = u64_offset + sizeof(u64_value);

    std::array<std::uint8_t, buf_size> buf{};

    write_uint<u8_offset>(u8_value, buf);
    write_uint<u16_offset>(u16_value, buf);
    write_uint<u32_offset>(u32_value, buf);
    write_uint<u64_offset>(u64_value, buf);

    std::uint8_t  u8_extracted{};
    std::uint16_t u16_extracted{};
    std::uint32_t u32_extracted{};
    std::uint64_t u64_extracted{};

    decode_uint<u8_offset>(buf, u8_extracted);
    decode_uint<u16_offset>(buf, u16_extracted);
    decode_uint<u32_offset>(buf, u32_extracted);
    decode_uint<u64_offset>(buf, u64_extracted);

    EXPECT_EQ(u8_value, u8_extracted);
    EXPECT_EQ(u16_value, u16_extracted);
    EXPECT_EQ(u32_value, u32_extracted);
    EXPECT_EQ(u64_value, u64_extracted);
}

TEST(EncodingTests, DecodeUIntVectorTest) { // !NOLINT
    const std::uint8_t  u8_value{random<std::uint8_t>()};
    const std::uint16_t u16_value{random<std::uint16_t>()};
    const std::uint32_t u32_value{random<std::uint32_t>()};
    const std::uint64_t u64_value{random<std::uint64_t>()};

    constexpr auto u8_offset  = 0UL;
    constexpr auto u16_offset = u8_offset + sizeof(u8_value);
    constexpr auto u32_offset = u16_offset + sizeof(u16_value);
    constexpr auto u64_offset = u32_offset + sizeof(u32_value);

    std::vector<std::uint8_t> buf{};

    append_uint(u8_value, buf);
    append_uint(u16_value, buf);
    append_uint(u32_value, buf);
    append_uint(u64_value, buf);

    std::uint8_t  u8_extracted{};
    std::uint16_t u16_extracted{};
    std::uint32_t u32_extracted{};
    std::uint64_t u64_extracted{};

    decode_uint<u8_offset>(buf, u8_extracted);
    decode_uint<u16_offset>(buf, u16_extracted);
    decode_uint<u32_offset>(buf, u32_extracted);
    decode_uint<u64_offset>(buf, u64_extracted);

    EXPECT_EQ(u8_value, u8_extracted);
    EXPECT_EQ(u16_value, u16_extracted);
    EXPECT_EQ(u32_value, u32_extracted);
    EXPECT_EQ(u64_value, u64_extracted);
}

} // namespace ztech::zp::tests
