#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <type_traits>
#include <vector>

namespace ztech::zp {

/*!
 * A class to represent a message
 *
 * \tparam protocol_version The protocol version the message belongs to
 * \tparam request          If true, the class represents a request, otherwise,
 *                          the class represents a response
 */
template <std::uint8_t version, bool is_request>
class message {
    using header_type = ztech::zp::message_header<version, is_request>;

  public:
    /*!
     * \brief Default constructor
     *
     * \param[in] header The message header
     * \param[in] body   The message body
     */
    message(header_type header, std::vector<std::uint8_t>&& body)
        : header_{header}, body_{std::move(body)} {
        assert(header_.body_length == body_.size());
    }

    /*!
     * \brief Gets the header of the message
     * \return A constant reference to the header of the message
     */
    [[nodiscard]] inline auto header() const noexcept -> const header_type& {
        return header_;
    }

    /*!
     * \brief Gets the body of the message
     * \return A constant reference to the body of the message
     */
    [[nodiscard]] inline auto body() const noexcept
        -> const std::vector<std::uint8_t>& {
        return body_;
    }

    /*!
     * \brief Encodes a message into a flat buffer container the binary data
     *        ready to be sent across the wire.
     * \return A buffer containing the binary data of the message
     */
    [[nodiscard]] auto flatten() const noexcept -> std::vector<std::uint8_t> {
        std::vector<std::uint8_t> retbuf{};

        header_.encode(retbuf);
        std::copy(std::cbegin(body_), std::cend(body_),
                  std::back_inserter<>(retbuf));

        return retbuf;
    }

  private:
    header_type               header_;
    std::vector<std::uint8_t> body_;
};

/*!
 * \brief An alias for a message of type request
 * \tparam version The protocol version the message belongs to
 */
template <std::uint8_t version>
using request = message<version, true>;

/*!
 * \brief An alias for a message of type request
 * \tparam version The protocol version the message belongs to
 */
template <std::uint8_t version>
using response = message<version, false>;

} // namespace ztech::zp

#endif
