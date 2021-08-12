#ifndef ZTECH_ZP_DETAIL_ENCODING_HPP
#define ZTECH_ZP_DETAIL_ENCODING_HPP

#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace ztech::zp::detail {

template <std::size_t i, typename T>
requires std::is_unsigned_v<T>
constexpr auto get_nth_byte(T value) -> std::uint8_t {
    static_assert(i < sizeof(T));

    return (value >> (8 * (sizeof(T) - i - 1))) & 0xFF;
}

template <typename T>
requires std::is_unsigned_v<T>
constexpr auto get_nth_byte(T value, std::size_t i) -> std::uint8_t {
    assert(i < sizeof(T));

    return (value >> (8 * (sizeof(T) - i - 1))) & 0xFF;
}

template <std::size_t offset, typename T, std::size_t array_size,
          std::size_t i = 0>
requires std::is_unsigned_v<T>
void write_uint(T value, std::array<std::uint8_t, array_size>& buf) {
    static_assert(i < sizeof(T));
    static_assert(offset + i + 1 <= array_size);

    buf[offset + i] = get_nth_byte<i>(value);

    if constexpr (i < sizeof(T) - 1) {
        write_uint<offset, T, array_size, i + 1>(value, buf);
    }
}

template <typename T, std::size_t i = 0>
requires std::is_unsigned_v<T>
void append_uint(T value, std::vector<std::uint8_t>& buf) {
    static_assert(i < sizeof(T));

    buf.emplace_back(get_nth_byte<i>(value));

    if constexpr (i < sizeof(T) - 1) {
        append_uint<T, i + 1>(value, buf);
    }
}

} // namespace ztech::zp::detail

#endif
