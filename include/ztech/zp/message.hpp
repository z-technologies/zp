#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <type_traits>
#include <vector>

namespace ztech::zp {

/*!
 * A class to represent a message
 */
class message {
  public:
    /*!
     * \brief Default constructor
     *
     * \param[in] header The message header
     * \param[in] body   The message body
     */
    message(ztech::zp::message_header header, std::vector<std::uint8_t>&& body)
        : header_{header}, body_{std::move(body)} {
        assert(header_.body_length == body_.size());
    }

    /*!
     * \brief Gets the header of the message
     * \return A constant reference to the header of the message
     */
    [[nodiscard]] inline auto header() const noexcept
        -> const ztech::zp::message_header& {
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
    ztech::zp::message_header header_;
    std::vector<std::uint8_t> body_;
};

} // namespace ztech::zp

#endif
