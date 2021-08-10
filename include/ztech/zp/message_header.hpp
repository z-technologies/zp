#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/flags.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace ztech::zp {

struct message_header {
    static constexpr std::size_t size{14UL};
    static constexpr std::size_t max_body_length{
        std::numeric_limits<std::uint32_t>::max()};

    std::uint16_t    type;
    std::uint16_t    command;
    ztech::zp::flags flags;
    std::uint32_t    tag;
    std::uint32_t    body_length;

    void encode(std::array<std::uint8_t, size>& buf) const noexcept;
};

static_assert(message_header::size ==
              (sizeof(std::declval<message_header>().type) +
               sizeof(std::declval<message_header>().command) +
               sizeof(std::declval<message_header>().tag) +
               sizeof(std::declval<message_header>().flags) +
               sizeof(std::declval<message_header>().body_length)));

} // namespace ztech::zp

#endif
