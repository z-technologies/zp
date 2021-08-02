#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <vector>

namespace ztech::zp::inline v1 {

class message {
  public:
    message(ztech::zp::v1::message_header header,
            std::vector<std::uint8_t>&&   body)
        : header_{header}, body_{std::move(body)} {
    }

    [[nodiscard]] inline auto header() const noexcept
        -> const ztech::zp::v1::message_header& {
        return header_;
    }

    [[nodiscard]] inline auto body() const noexcept
        -> const std::vector<std::uint8_t>& {
        return body_;
    }

  private:
    ztech::zp::v1::message_header header_;
    std::vector<std::uint8_t>     body_;
};

} // namespace ztech::zp::inline v1

#endif
