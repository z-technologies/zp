#include "ztech/zp/message_header.hpp"

#include <boost/endian.hpp>

#include <array>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

namespace {

template <std::size_t offset, typename T, std::size_t size = sizeof(T)>
requires std::is_unsigned_v<T>
inline void
encode_uint(T                                                          val,
            std::array<std::uint8_t, ztech::zp::message_header::size>& buf) {
    static_assert(size >= 1 && size <= 4 && size <= sizeof(T));
    static_assert(offset + size <= ztech::zp::message_header::size);

    buf[offset + sizeof(T) - size] =
        (val >> (8 * (size - 1))) & 0xFF; // !NOLINT

    if constexpr (size - 1 > 0) {
        encode_uint<offset, T, size - 1>(val, buf);
    }
}

} // namespace

namespace ztech::zp {

void message_header::encode(
    std::array<std::uint8_t, size>& buf) const noexcept {
    constexpr std::size_t type_offset{0};
    constexpr std::size_t command_offset{type_offset + sizeof(type)};
    constexpr std::size_t flags_offset{command_offset + sizeof(command)};
    constexpr std::size_t tag_offset{flags_offset + sizeof(flags)};
    constexpr std::size_t body_length_offset{tag_offset + sizeof(tag)};

    static_assert(type_offset == 0);
    static_assert(command_offset == 2);
    static_assert(flags_offset == 4);
    static_assert(tag_offset == 6);
    static_assert(body_length_offset == 10);

    ::encode_uint<type_offset>(type, buf);
    ::encode_uint<command_offset>(command, buf);
    ::encode_uint<flags_offset>(static_cast<flags_underlying_type>(flags), buf);
    ::encode_uint<tag_offset>(tag, buf);
    ::encode_uint<body_length_offset>(body_length, buf);
}

} // namespace ztech::zp
