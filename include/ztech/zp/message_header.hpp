#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/detail/encoding.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace ztech::zp {

template <std::uint8_t version>
concept is_valid_protocol_version = requires {
    version < 0x7F;
};

template <std::uint8_t protocol_version, bool request>
requires is_valid_protocol_version<protocol_version>
struct message_header {
    static constexpr auto size       = 13UL;
    static constexpr auto version    = protocol_version;
    static constexpr auto is_request = request;

    std::uint16_t type;
    std::uint16_t command;
    std::uint32_t tag;
    std::uint32_t body_length;

    void encode(std::array<std::uint8_t, size>& buf) const noexcept {
        constexpr std::size_t version_offset{0UL};
        constexpr std::size_t type_offset{version_offset + sizeof(version)};
        constexpr std::size_t command_offset{type_offset + sizeof(type)};
        constexpr std::size_t tag_offset{command_offset + sizeof(command)};
        constexpr std::size_t body_length_offset{tag_offset + sizeof(tag)};

        static_assert(version_offset == 0UL);
        static_assert(type_offset == 1UL);
        static_assert(command_offset == 3UL);
        static_assert(tag_offset == 5UL);
        static_assert(body_length_offset == 9UL);

        ztech::zp::detail::write_uint<version_offset>(
            get_version_request_byte(), buf);
        ztech::zp::detail::write_uint<type_offset>(type, buf);
        ztech::zp::detail::write_uint<command_offset>(command, buf);
        ztech::zp::detail::write_uint<tag_offset>(tag, buf);
        ztech::zp::detail::write_uint<body_length_offset>(body_length, buf);
    }

    void encode(std::vector<std::uint8_t>& buf) const noexcept {
        ztech::zp::detail::append_uint(get_version_request_byte(), buf);
        ztech::zp::detail::append_uint(type, buf);
        ztech::zp::detail::append_uint(command, buf);
        ztech::zp::detail::append_uint(tag, buf);
        ztech::zp::detail::append_uint(body_length, buf);
    }

    static constexpr auto get_version_request_byte() -> std::uint8_t {
        return (version << 1U) | (is_request ? 1U : 0U);
    }

    static_assert(size == (1U + sizeof(type) + sizeof(command) + sizeof(tag) +
                           sizeof(body_length)));
};

} // namespace ztech::zp

#endif
