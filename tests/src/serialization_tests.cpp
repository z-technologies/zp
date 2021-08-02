#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/serialization.hpp"

#include "gtest/gtest.h"

#include "msgpack/adaptor/string.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace ztech::zp::tests::util;

namespace ztech::zp::tests {
namespace {

constexpr auto test_string_size = 0xFF;

struct test_model {
    std::uint8_t  uint8_value;
    std::uint16_t uint16_value;
    std::uint32_t uint32_value;
    std::uint64_t uint64_value;
    std::int8_t   int8_value;
    std::int16_t  int16_value;
    std::int32_t  int32_value;
    std::int64_t  int64_value;

    bool   bool_value;
    float  float_value;
    double double_value;

    std::string string_value;

    inline auto operator==(const test_model& rhs) const noexcept
        -> bool = default;

    ZP_DEFINE(uint8_value, uint16_value, uint32_value, uint64_value, int8_value,
              int16_value, int32_value, int64_value, bool_value, float_value,
              double_value, string_value);
};

template <typename T, typename Container>
inline void test_type(Container& c, const T& value) {
    c.clear();
    ztech::zp::util::serialize(c, value);

    T    out_value{};
    auto success = ztech::zp::util::deserialize(c, out_value);

    ASSERT_EQ(value, out_value);
    ASSERT_TRUE(success);
}

template <typename T, typename Container>
requires std::is_fundamental_v<T> &&
    ztech::zp::util::detail::writable_buffer<Container>
inline void test_fundamental_type(Container& c) {
    test_type(c, random<T>());
}

} // namespace

TEST(SerializationTests, STLPrimitiveTypesTest) { // !NOLINT
    std::vector<std::uint8_t>              buf{};
    ztech::zp::util::stl_container_wrapper wrapper{buf};

    test_fundamental_type<bool>(wrapper);
    test_fundamental_type<std::uint8_t>(wrapper);
    test_fundamental_type<std::uint16_t>(wrapper);
    test_fundamental_type<std::uint32_t>(wrapper);
    test_fundamental_type<std::uint64_t>(wrapper);
    test_fundamental_type<float>(wrapper);
    test_fundamental_type<double>(wrapper);
}

TEST(SerializationTests, MsgPackBufferPrimitiveTypesTest) { // !NOLINT
    msgpack::sbuffer buf{};

    test_fundamental_type<bool>(buf);
    test_fundamental_type<std::uint8_t>(buf);
    test_fundamental_type<std::uint16_t>(buf);
    test_fundamental_type<std::uint32_t>(buf);
    test_fundamental_type<std::uint64_t>(buf);
    test_fundamental_type<float>(buf);
    test_fundamental_type<double>(buf);
}

TEST(SerializationTests, StringTest) { // !NOLINT
    msgpack::sbuffer buf{};

    auto random_str =
        random_string(test_string_size, random_string_options::mixed);

    test_type(buf, random_str);
}

TEST(SerializationTests, ModelTest) { // !NOLINT
    msgpack::sbuffer buf{};

    test_model random_model{
        .uint8_value  = random<std::uint8_t>(),
        .uint16_value = random<std::uint16_t>(),
        .uint32_value = random<std::uint32_t>(),
        .uint64_value = random<std::uint64_t>(),
        .int8_value   = random<std::int8_t>(),
        .int16_value  = random<std::int16_t>(),
        .int32_value  = random<std::int32_t>(),
        .int64_value  = random<std::int64_t>(),
        .bool_value   = random<bool>(),
        .float_value  = random<float>(),
        .double_value = random<double>(),
        .string_value =
            random_string(test_string_size, random_string_options::mixed)};

    test_type(buf, random_model);
}

} // namespace ztech::zp::tests
