#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <vector>

namespace ztech::zp {

class message {
  public:
    message(ztech::zp::message_header header, std::vector<std::uint8_t>&& body)
        : header_{header}, body_{std::move(body)} {
    }

    [[nodiscard]] inline auto header() const noexcept
        -> const ztech::zp::message_header& {
        return header_;
    }

    [[nodiscard]] inline auto body() const noexcept
        -> const std::vector<std::uint8_t>& {
        return body_;
    }

  private:
    ztech::zp::message_header header_;
    std::vector<std::uint8_t> body_;
};

} // namespace ztech::zp

#endif
