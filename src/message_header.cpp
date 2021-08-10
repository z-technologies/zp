#include "ztech/zp/message_header.hpp"
#include "ztech/zp/detail/encoding.hpp"

#include <boost/endian.hpp>

#include <array>
#include <cstdint>
#include <vector>

namespace ztech::zp {

void message_header::encode(
    std::array<std::uint8_t, size>& buf) const noexcept {
    constexpr std::size_t version_offset{0UL};
    constexpr std::size_t type_offset{version_offset + sizeof(version)};
    constexpr std::size_t command_offset{type_offset + sizeof(type)};
    constexpr std::size_t flags_offset{command_offset + sizeof(command)};
    constexpr std::size_t tag_offset{flags_offset + sizeof(flags)};
    constexpr std::size_t body_length_offset{tag_offset + sizeof(tag)};

    static_assert(version_offset == 0UL);
    static_assert(type_offset == 1UL);
    static_assert(command_offset == 3UL);
    static_assert(flags_offset == 5UL);
    static_assert(tag_offset == 6UL);
    static_assert(body_length_offset == 10UL);

    ztech::zp::detail::write_uint<version_offset>(version, buf);
    ztech::zp::detail::write_uint<type_offset>(type, buf);
    ztech::zp::detail::write_uint<command_offset>(command, buf);
    ztech::zp::detail::write_uint<flags_offset>(
        static_cast<flags_underlying_type>(flags), buf);
    ztech::zp::detail::write_uint<tag_offset>(tag, buf);
    ztech::zp::detail::write_uint<body_length_offset>(body_length, buf);
}

void message_header::encode(std::vector<std::uint8_t>& buf) const noexcept {
    ztech::zp::detail::append_uint(version, buf);
    ztech::zp::detail::append_uint(type, buf);
    ztech::zp::detail::append_uint(command, buf);
    ztech::zp::detail::append_uint(static_cast<flags_underlying_type>(flags),
                                   buf);
    ztech::zp::detail::append_uint(tag, buf);
    ztech::zp::detail::append_uint(body_length, buf);
}

} // namespace ztech::zp
