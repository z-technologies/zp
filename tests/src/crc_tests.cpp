#include "ztech/zp/crc.hpp"

#include "gtest/gtest.h"

#include <cstdint>
#include <string_view>

namespace ztech::zp::tests {

TEST(CRCRust, CRC16Tests) { // !NOLINT
    constexpr std::string_view test_raw_str_value{"Hello, World"};
    constexpr std::uint16_t    test_raw_str_crc16_actual{0x4C79};

    ztech::zp::crc_calculator<std::uint16_t> test_raw_str_crc16_result{};
    test_raw_str_crc16_result.process(test_raw_str_value.data(),
                                      test_raw_str_value.size());
    EXPECT_EQ(test_raw_str_crc16_result.value(), test_raw_str_crc16_actual);
}

TEST(CRCRust, CRC32Tests) { // !NOLINT
    constexpr std::string_view test_raw_str_value{"Hello, World"};
    constexpr std::uint32_t    test_raw_str_crc32_actual{0x265B86C6};

    ztech::zp::crc_calculator<std::uint32_t> test_raw_str_crc32_result{};
    test_raw_str_crc32_result.process(test_raw_str_value.data(),
                                      test_raw_str_value.size());
    EXPECT_EQ(test_raw_str_crc32_result.value(), test_raw_str_crc32_actual);
}

} // namespace ztech::zp::tests
