#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/serialization.hpp"

#include "msgpack/sbuffer.hpp"
#include "gtest/gtest.h"

#include "msgpack/adaptor/bool.hpp"
#include "msgpack/adaptor/float.hpp"
#include "msgpack/adaptor/int.hpp"

#include <cstdint>
#include <iostream>
#include <type_traits>
#include <vector>

namespace ztech::zp::tests {

template <typename T, typename Container>
requires std::is_fundamental_v<T> &&
    ztech::zp::util::detail::writable_buffer<Container>
inline void test_fundamental_type(Container& c) {
    auto random_value = ztech::zp::tests::util::random<T>();

    c.clear();
    ztech::zp::util::serialize(c, random_value);

    T out_value{};
    ztech::zp::util::deserialize(c, out_value);

    ASSERT_EQ(random_value, out_value);
}

TEST(SerializationTests, STLPrimitiveTypesTest) {
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

TEST(SerializationTests, MsgPackBufferPrimitiveTypesTest) {
    msgpack::sbuffer buf{};

    test_fundamental_type<bool>(buf);
    test_fundamental_type<std::uint8_t>(buf);
    test_fundamental_type<std::uint16_t>(buf);
    test_fundamental_type<std::uint32_t>(buf);
    test_fundamental_type<std::uint64_t>(buf);
    test_fundamental_type<float>(buf);
    test_fundamental_type<double>(buf);
}

} // namespace ztech::zp::tests
