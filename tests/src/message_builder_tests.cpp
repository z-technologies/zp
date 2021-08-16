#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/message_builder.hpp"

#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>

namespace ztech::zp::tests {

TEST(MessageBuilderTests, TestMessageBuilder) { // !NOLINT
    using namespace ztech::zp::tests::util;
    using ztech::zp::util::message_builder;

    const auto test_type  = random<std::uint16_t>();
    const auto test_extra = random<std::uint16_t>();
    const auto test_tag   = random<std::uint16_t>();
    const auto test_body  = random_vector<std::uint8_t, 0xFF>();

    const auto msg =
        message_builder{test_type, test_extra, test_tag}.build(test_body);

    EXPECT_EQ(msg.header().type, test_type);
    EXPECT_EQ(msg.header().extra, test_extra);
    EXPECT_EQ(msg.header().tag, test_tag);
    EXPECT_EQ(msg.header().body_length, test_body.size());
    EXPECT_TRUE(std::equal(std::cbegin(test_body), std::cend(test_body),
                           std::cbegin(msg.body()), std::cend(msg.body())));
}

} // namespace ztech::zp::tests
