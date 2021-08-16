#include "ztech/zp/detail/encoding.hpp"
#include "ztech/zp/message.hpp"
#include "ztech/zp/tests/util/random.hpp"
#include "ztech/zp/util/message_builder.hpp"

#include "gtest/gtest.h"

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <vector>

using namespace ztech::zp::tests::util;

namespace ztech::zp::tests {

TEST(MessageTests, MessageFlattenTest) { // !NOLINT
    const auto test_type  = random<std::uint16_t>();
    const auto test_extra = random<std::uint16_t>();
    const auto test_tag   = random<std::uint16_t>();

    auto test_body = random_vector<std::uint8_t, 0xFF>();

    ztech::zp::message_header header{
        .type        = test_type,
        .extra       = test_extra,
        .tag         = test_tag,
        .body_length = static_cast<std::uint32_t>(test_body.size())};

    ztech::zp::message msg{header, std::move(test_body)};

    std::vector<std::uint8_t> test_buf{};
    msg.header().encode(test_buf);

    std::copy(std::cbegin(msg.body()), std::cend(msg.body()),
              std::back_inserter<>(test_buf));

    const auto ret_buf = msg.flatten();

    ASSERT_EQ(test_buf.size(), ret_buf.size());
    ASSERT_TRUE(std::equal(std::cbegin(test_buf), std::cend(test_buf),
                           std::cbegin(ret_buf), std::cend(ret_buf)));
}

} // namespace ztech::zp::tests
