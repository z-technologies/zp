#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/detail/encoding.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

namespace ztech::zp {

//! \brief The size of the message header in bytes
constexpr std::size_t message_header_size{13UL};

/*!
 * \brief A concept to check that a protocol version value is valid.
 *
 * Protocol version values must be less than or equal to 127 (0b01111111) in
 * binary. This is a requirement because the last bit in the first byte of the
 * message is used to store whether the message resembles a request (1) or a
 * response (0).
 *
 * \tparam version  The protocol version value to be checked
 */
template <std::uint8_t version>
concept is_valid_protocol_version = requires {
    version < 0x7F;
};

/*!
 * \brief A class to represent messages headers.
 *
 * This class can represent either a request or a response depending on
 * \p request value.
 *
 * \tparam protocol_version The protocol version the message belongs to
 * \tparam request          If true, the class represents a request, otherwise,
 *                          the class represents a response
 */
template <std::uint8_t protocol_version, bool request>
requires is_valid_protocol_version<protocol_version>
struct message_header {
    static constexpr auto version    = protocol_version;
    static constexpr auto is_request = request;

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

    /*!
     * \brief Encodes the header fields into a fixed-sized buffer, \p buf.
     *
     * This function encodes the fields of the header into the buffer \p buf.
     * The fields are encoded in the network-order (Big Endian Ordering).
     *
     * \param[out] buf The buffer into which to encode the header fields
     */
    void
    encode(std::array<std::uint8_t, message_header_size>& buf) const noexcept {
        ztech::zp::detail::write_uint<version_offset>(get_first_byte(), buf);
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
        ztech::zp::detail::append_uint(get_first_byte(), buf);
        ztech::zp::detail::append_uint(type, buf);
        ztech::zp::detail::append_uint(extra, buf);
        ztech::zp::detail::append_uint(tag, buf);
        ztech::zp::detail::append_uint(body_length, buf);
    }

    /*!
     * \brief Decodes a header from the buffer \p buf
     *
     * \param[in] buf  The buffer from which to decode the header
     *
     * \return The decoded header
     */
    static auto decode(const std::array<std::uint8_t, message_header_size>& buf)
        -> message_header<version, is_request> {
        assert((buf[0] >> 1U) == version);
        assert((buf[0] & 1U) == (is_request ? 1 : 0));

        message_header<version, is_request> ret{};
        ztech::zp::detail::decode_uint<type_offset>(buf, ret.type);
        ztech::zp::detail::decode_uint<extra_offset>(buf, ret.extra);
        ztech::zp::detail::decode_uint<tag_offset>(buf, ret.tag);
        ztech::zp::detail::decode_uint<body_length_offset>(buf,
                                                           ret.body_length);

        return ret;
    }

    /*!
     * \brief Decodes a header from the buffer \p buf
     *
     * \param[in] buf  The buffer from which to decode the header
     *
     * \return The decoded header
     */
    static auto decode(const std::vector<std::uint8_t>& buf)
        -> message_header<version, is_request> {
        assert(buf.size() >= message_header_size);
        assert((buf[0] >> 1U) == version);
        assert((buf[0] & 1U) == (is_request ? 1 : 0));

        message_header<version, is_request> ret{};
        ztech::zp::detail::decode_uint<type_offset>(buf, ret.type);
        ztech::zp::detail::decode_uint<extra_offset>(buf, ret.extra);
        ztech::zp::detail::decode_uint<tag_offset>(buf, ret.tag);
        ztech::zp::detail::decode_uint<body_length_offset>(buf,
                                                           ret.body_length);

        return ret;
    }

    static constexpr std::size_t version_offset{0UL};
    static constexpr std::size_t type_offset{version_offset + sizeof(version)};
    static constexpr std::size_t extra_offset{type_offset + sizeof(type)};
    static constexpr std::size_t tag_offset{extra_offset + sizeof(extra)};
    static constexpr std::size_t body_length_offset{tag_offset + sizeof(tag)};

  private:
    static constexpr auto get_first_byte() -> std::uint8_t {
        return (version << 1U) | (is_request ? 1U : 0U);
    }

    static_assert(message_header_size == (1U + sizeof(type) + sizeof(extra) +
                                          sizeof(tag) + sizeof(body_length)));

    static_assert(version_offset == 0UL);
    static_assert(type_offset == 1UL);
    static_assert(extra_offset == 3UL);
    static_assert(tag_offset == 5UL);
    static_assert(body_length_offset == 9UL);
};

} // namespace ztech::zp

#endif
