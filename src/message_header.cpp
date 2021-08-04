#include "ztech/zp/message_header.hpp"

#include <boost/endian.hpp>

#include <array>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

namespace {

template <typename T, std::size_t size = sizeof(T)>
requires std::is_unsigned_v<T>
inline void add_uint_bytes(T val, std::uint8_t& out) {
    static_assert(size >= 1 && size <= 4 && size <= sizeof(T));

    out += (val >> (8 * (size - 1))) & 0xFF;

    if constexpr (size - 1 > 0) {
        add_uint_bytes<T, size - 1>(val, out);
    }
}

template <std::size_t offset, typename T, std::size_t size = sizeof(T)>
requires std::is_unsigned_v<T>
inline void encode_uint(
    T val, std::array<std::uint8_t, ztech::zp::v1::message_header::size>& buf) {
    static_assert(size >= 1 && size <= 4 && size <= sizeof(T));
    static_assert(offset + size <= ztech::zp::v1::message_header::size);

    buf[offset + sizeof(T) - size] = (val >> (8 * (size - 1))) & 0xFF;

    if constexpr (size - 1 > 0) {
        encode_uint<offset, T, size - 1>(val, buf);
    }
}

} // namespace

namespace ztech::zp::inline v1 {

void message_header::update_checksum() noexcept {
    header_checksum = 0;

    ::add_uint_bytes(version, header_checksum);
    ::add_uint_bytes(type, header_checksum);
    ::add_uint_bytes(command, header_checksum);
    ::add_uint_bytes(static_cast<flags_underlying_type>(flags),
                     header_checksum);
    ::add_uint_bytes(tag, header_checksum);
    ::add_uint_bytes(body_length, header_checksum);

    header_checksum = ~header_checksum;
}

void message_header::encode(std::array<std::uint8_t, size>& buf) noexcept {
    constexpr std::size_t version_offset{0};
    constexpr std::size_t type_offset{version_offset + sizeof(version)};
    constexpr std::size_t command_offset{type_offset + sizeof(type)};
    constexpr std::size_t flags_offset{command_offset + sizeof(command)};
    constexpr std::size_t tag_offset{flags_offset + sizeof(flags)};
    constexpr std::size_t body_length_offset{tag_offset + sizeof(tag)};
    constexpr std::size_t header_checksum_offset{body_length_offset +
                                                 sizeof(body_length)};

    static_assert(version_offset == 0);
    static_assert(type_offset == 1);
    static_assert(command_offset == 3);
    static_assert(flags_offset == 5);
    static_assert(tag_offset == 7);
    static_assert(body_length_offset == 11);

    update_checksum();

    ::encode_uint<version_offset>(version, buf);
    ::encode_uint<type_offset>(type, buf);
    ::encode_uint<command_offset>(command, buf);
    ::encode_uint<flags_offset>(static_cast<flags_underlying_type>(flags), buf);
    ::encode_uint<tag_offset>(tag, buf);
    ::encode_uint<body_length_offset>(body_length, buf);
    ::encode_uint<header_checksum_offset>(header_checksum, buf);
}

} // namespace ztech::zp::inline v1
