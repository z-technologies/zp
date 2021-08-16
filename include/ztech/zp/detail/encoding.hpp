#ifndef ZTECH_ZP_DETAIL_ENCODING_HPP
#define ZTECH_ZP_DETAIL_ENCODING_HPP

#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace ztech::zp::detail {

/*!
 * \breif Gets the byte with the index of \p i in \p value.
 *
 * This function gets the byte with the index of \p i in \p value. The index
 * ranges from 0 to size of \p T, and from the most significant byte.
 * \p T is required to be an unsigned integeral type (i.e., std::uint8_t,
 * std::uint16_t, ...).
 *
 * \tparam i  The index of the byte to get
 * \tparam T  The type of the value to get the byte from
 *
 * \param[in] value  The value to get the byte from
 *
 * \return The byte with the index of \p i
 */
template <std::size_t i, typename T>
requires std::is_unsigned_v<T>
constexpr auto get_nth_byte(T value) -> std::uint8_t {
    static_assert(i < sizeof(T));

    return (value >> (8 * (sizeof(T) - i - 1))) & 0xFF;
}

/*!
 * \breif Gets the byte with the index of \p i in \p value.
 *
 * This function gets the byte with the index of \p i in \p value. The index
 * ranges from 0 to size of \p T, and from the most significant byte.
 * \p T is required to be an unsigned integeral type (i.e., std::uint8_t,
 * std::uint16_t, ...).
 *
 * \tparam T  The type of the value to get the byte from
 *
 * \param[in] value  The value to get the byte from
 * \param[in] i      The index of the byte to get
 *
 * \return The byte with the index of \p i
 */
template <typename T>
requires std::is_unsigned_v<T>
constexpr auto get_nth_byte(T value, std::size_t i) -> std::uint8_t {
    assert(i < sizeof(T));

    return (value >> (8 * (sizeof(T) - i - 1))) & 0xFF;
}

/*!
 * \brief Inserts the bytes of \p value into the passed array in big endian
 *        order in the passed offset specified by \p offset.
 *
 * \tparam offset     The index from which to start writing the bytes of
 *                    \p value
 * \tparam T          The type of the value to be inserted. This type has to be
 *                    of an unsigned integeral type
 * \tparam array_size The size of the buffer \p buf into which to write the
 *                    value
 * \tparam i          The current index into which to write the current byte
 *
 * \param[in]  value The value which to be written into \p buf
 * \param[out] buf   The buffer into which to write the value \p value
 */
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

/*!
 * \brief Appends the bytes of \p value to \p buf.
 *
 * \tparam T The type of the value to be inserted. This type has to be
 *           of an unsigned integeral type
 * \tparam i The current index into which to write the current byte
 *
 * \param[in]  value The value which to be written into \p buf
 * \param[out] buf   The buffer into which to write the value \p value
 */
template <typename T, std::size_t i = 0>
requires std::is_unsigned_v<T>
void append_uint(T value, std::vector<std::uint8_t>& buf) {
    static_assert(i < sizeof(T));

    buf.emplace_back(get_nth_byte<i>(value));

    if constexpr (i < sizeof(T) - 1) {
        append_uint<T, i + 1>(value, buf);
    }
}

template <std::size_t offset, typename T, std::size_t array_size,
          std::size_t i = 0>
requires std::is_unsigned_v<T>
void decode_uint(const std::array<std::uint8_t, array_size>& buf, T& out) {
    static_assert(i < sizeof(T));
    static_assert(offset + i + 1 <= array_size);

    out |= buf[offset + i];

    if constexpr (i < sizeof(T) - 1) {
        out <<= 8U;
        decode_uint<offset, T, array_size, i + 1>(buf, out);
    } 
}

template <std::size_t offset, typename T, std::size_t i = 0>
requires std::is_unsigned_v<T>
void decode_uint(const std::vector<std::uint8_t>& buf, T& out) {
    static_assert(i < sizeof(T));
    assert(buf.size() >= offset + sizeof(T));

    out |= buf[offset + i];

    if constexpr (i < sizeof(T) - 1) {
        out <<= 8U;
        decode_uint<offset, T, i + 1>(buf, out);
    }
}

} // namespace ztech::zp::detail

#endif
