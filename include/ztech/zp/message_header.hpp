#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/flags.hpp"

#include <cstdint>
#include <type_traits>

namespace ztech::zp {

namespace detail {

template <typename TExtra>
concept is_command_error_code = requires {
    std::is_enum_v<TExtra> &&std::is_base_of_v<std::uint16_t, TExtra>;
};

} // namespace detail

inline namespace v1 {

constexpr std::uint8_t version = 0x01;

template <typename TExtra>
requires ztech::zp::detail::is_command_error_code<TExtra>
struct message_header {
    std::uint8_t         version : 4;
    std::uint16_t        type    : 12;
    TExtra               command;
    ztech::zp::v1::flags flags;
    std::uint16_t        tag;
    std::uint16_t        body_length;
    std::uint16_t        actual_length;
};

} // namespace v1
} // namespace ztech::zp

#endif
