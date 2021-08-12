#include "ztech/zp/message_header.hpp"
#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/message_builder.hpp"

#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>

using namespace ztech::zp::tests::util;

namespace {

template <std::uint8_t version, bool is_request>
void test_message_builder() {
    const auto test_type    = random<std::uint16_t>();
    const auto test_command = random<std::uint16_t>();
    const auto test_tag     = random<std::uint16_t>();
    const auto test_body    = random_vector<std::uint8_t, 0xFF>();

    const auto msg = ztech::zp::util::make_message_builder<version, is_request>(
                         test_type, test_command, test_tag)
                         .with_body(test_body)
                         .build();

    EXPECT_EQ(msg.header().type, test_type);
    EXPECT_EQ(msg.header().command, test_command);
    EXPECT_EQ(msg.header().tag, test_tag);
    EXPECT_EQ(msg.header().body_length, test_body.size());
    EXPECT_TRUE(std::equal(std::cbegin(test_body), std::cend(test_body),
                           std::cbegin(msg.body()), std::cend(msg.body())));
}

} // namespace

namespace ztech::zp::tests {

TEST(MessageBuilderTests, TestRequestMessageBuilder) { // !NOLINT
    ::test_message_builder<0x07, true>();
}

TEST(MessageBuilderTests, TestResponseMessageBuilder) { // !NOLINT
    ::test_message_builder<0x07, false>();
}

} // namespace ztech::zp::tests
