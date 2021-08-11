#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <vector>

namespace ztech::zp {

class message {
    using body_crc_type = std::uint32_t;

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

    [[nodiscard]] auto flatten() const noexcept -> std::vector<std::uint8_t>;

  private:
    ztech::zp::message_header header_;
    std::vector<std::uint8_t> body_;
};

} // namespace ztech::zp

#endif
