#include "ztech/zp/crc.hpp"
#include "ztech/zp/detail/encoding.hpp"
#include "ztech/zp/message.hpp"
#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/message_builder.hpp"

#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <vector>

using ztech::zp::tests::util::random;
using ztech::zp::util::message_builder;

namespace ztech::zp::tests {

TEST(MessageTests, FlattenTest) { // !NOLINT
    const auto test_type    = random<std::uint16_t>();
    const auto test_command = random<std::uint16_t>();
    const auto test_flags =
        static_cast<ztech::zp::flags>(random<std::uint16_t>());
    const auto test_tag = random<std::uint16_t>();

    const auto message = message_builder{}
                             .with_type(test_type)
                             .with_command(test_command)
                             .with_flags(test_flags)
                             .with_tag(test_tag)
                             .include_body_checksum()
                             .build();

    std::vector<std::uint8_t> test_buf{};
    message.header().encode(test_buf);
    std::copy(std::cbegin(message.body()), std::cend(message.body()),
              std::back_inserter<>(test_buf));

    ztech::zp::crc_calculator<ztech::zp::message::body_crc_type> crc_calc{};
    crc_calc.process(message.body());
    ztech::zp::detail::append_uint(crc_calc.value(), test_buf);

    const auto ret_buf = message.flatten();

    ASSERT_EQ(test_buf.size(), ret_buf.size());
    ASSERT_TRUE(std::equal(std::cbegin(test_buf), std::cend(test_buf),
                           std::cbegin(ret_buf), std::cend(ret_buf)));
}

} // namespace ztech::zp::tests