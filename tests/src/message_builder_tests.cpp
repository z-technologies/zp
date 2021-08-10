#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/message_builder.hpp"

#include "gtest/gtest.h"

#include <cstdint>

using ztech::zp::tests::util::random;
using ztech::zp::util::message_builder;

namespace ztech::zp::tests {

TEST(MessageBuilderTests, HeaderBuildingTest) { // !NOLINT
    const auto test_type    = random<std::uint16_t>();
    const auto test_command = random<std::uint16_t>();
    const auto test_flags =
        static_cast<ztech::zp::flags>(random<std::uint16_t>());
    const auto test_tag = random<std::uint16_t>();

    auto message = message_builder{}
                       .with_type(test_type)
                       .with_command(test_command)
                       .with_flags(test_flags)
                       .with_tag(test_tag)
                       .build();

    EXPECT_EQ(message.header().type, test_type);
    EXPECT_EQ(message.header().command, test_command);
    EXPECT_EQ(message.header().flags, test_flags);
    EXPECT_EQ(message.header().tag, test_tag);
    EXPECT_EQ(message.header().body_length, 0);
    EXPECT_EQ(message.body().size(), 0);
}

} // namespace ztech::zp::tests
