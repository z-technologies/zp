#ifndef ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP
#define ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP

#include "ztech/zp/message.hpp"
#include "ztech/zp/message_header.hpp"
#include "ztech/zp/util/serialization.hpp"

#include <cstdint>
#include <vector>

namespace ztech::zp::util {

/*!
 * \brief A class to abstract message header building logic
 *
 * This class is used as the first step in the message building process.
 */
struct message_builder {
    /*!
     * \brief Default constrcutor
     *
     * \param[in] type  The type of the message
     * \param[in] extra The value of the message's extra field
     * \param[in] tag   The tag of the message
     */
    message_builder(std::uint16_t type, std::uint16_t extra, std::uint32_t tag)
        : header_{.type = type, .extra = extra, .tag = tag, .body_length = 0U} {
    }

    /*!
     * \brief Generates an instance of \a message_builder with \p body
     *
     * \param[in] body An rvalue of the body of the message to be used
     * \return An instance of \a message_builder with the \p body value
     */
    [[nodiscard]] inline auto build(std::vector<std::uint8_t> body)
        -> ztech::zp::message {
        header_.body_length = body.size();
        return ztech::zp::message{header_, std::move(body)};
    }

    /*!
     * \brief Generates an instance of \a message_builder with the
     *        data in \p value serialized into a buffer
     *
     * \param[in] value The value which to serialize
     * \return An instance of \a message_builder with the \p body value
     */
    template <typename T>
    [[nodiscard]] inline auto build(const T& value) -> ztech::zp::message {
        std::vector<std::uint8_t> body{};
        ztech::zp::util::serialize(body, value);
        return build(std::move(body));
    }

  private:
    ztech::zp::message_header header_{};
};

} // namespace ztech::zp::util

#endif
