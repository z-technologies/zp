#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/detail/encoding.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace ztech::zp {

/*!
 * \brief A class to represent messages headers.
 */
struct message_header {
    //! \brief The size of the message header in bytes

    /*!
     * \brief The type of the message.
     *
     * This field represents the type of the message. The type can be thought
     * of as the category of the request.
     */
    std::uint16_t type;

    /*!
     * \brief An extra field for the request.
     *
     * This field can be used to store the command identifier for requests, or
     * the response error code for responses.
     */
    std::uint16_t extra;

    /*!
     * \brief The tag value of the requests.
     *
     * This field represents an additional value that is used to distinguish
     * requests when sent in an asynchronous fashion.
     */
    std::uint32_t tag;

    /*!
     * \brief the message body length
     */
    std::uint32_t body_length;

    static constexpr std::size_t type_offset{0UL};
    static constexpr std::size_t extra_offset{type_offset + sizeof(type)};
    static constexpr std::size_t tag_offset{extra_offset + sizeof(extra)};
    static constexpr std::size_t body_length_offset{tag_offset + sizeof(tag)};
    static constexpr std::size_t size{body_length_offset + sizeof(body_length)};

    /*!
     * \brief Encodes the header fields into a fixed-sized buffer, \p buf.
     *
     * This function encodes the fields of the header into the buffer \p buf.
     * The fields are encoded in the network-order (Big Endian Ordering).
     *
     * \param[out] buf The buffer into which to encode the header fields
     */
    void encode(std::array<std::uint8_t, size>& buf) const noexcept {
        ztech::zp::detail::write_uint<type_offset>(type, buf);
        ztech::zp::detail::write_uint<extra_offset>(extra, buf);
        ztech::zp::detail::write_uint<tag_offset>(tag, buf);
        ztech::zp::detail::write_uint<body_length_offset>(body_length, buf);
    }

    /*!
     * \brief Encodes the header fields into a variable-sized buffer, \p buf.
     *
     * This function encodes the fields of the header into the buffer \p buf.
     * The fields are encoded in the network-order (Big Endian Ordering).
     *
     * \param[out] buf The buffer into which to encode the header fields
     */
    void encode(std::vector<std::uint8_t>& buf) const noexcept {
        ztech::zp::detail::append_uint(type, buf);
        ztech::zp::detail::append_uint(extra, buf);
        ztech::zp::detail::append_uint(tag, buf);
        ztech::zp::detail::append_uint(body_length, buf);
    }

    /*!
     * \brief Decodes a header from the buffer \p buf
     *
     * \param[in] buf  The buffer from which to decode the header
     */
    void decode(const std::array<std::uint8_t, size>& buf) {
        ztech::zp::detail::decode_uint<type_offset>(buf, type);
        ztech::zp::detail::decode_uint<extra_offset>(buf, extra);
        ztech::zp::detail::decode_uint<tag_offset>(buf, tag);
        ztech::zp::detail::decode_uint<body_length_offset>(buf, body_length);
    }

    /*!
     * \brief Decodes a header from the buffer \p buf
     *
     * \param[in] buf  The buffer from which to decode the header
     */
    void decode(const std::vector<std::uint8_t>& buf) {
        ztech::zp::detail::decode_uint<type_offset>(buf, type);
        ztech::zp::detail::decode_uint<extra_offset>(buf, extra);
        ztech::zp::detail::decode_uint<tag_offset>(buf, tag);
        ztech::zp::detail::decode_uint<body_length_offset>(buf, body_length);
    }

    static_assert(type_offset == 0UL);
    static_assert(extra_offset == 2UL);
    static_assert(tag_offset == 4UL);
    static_assert(body_length_offset == 8UL);
    static_assert(size == 12UL);
};

} // namespace ztech::zp

#endif
