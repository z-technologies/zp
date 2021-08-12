#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <type_traits>
#include <vector>

namespace ztech::zp {

template <std::uint8_t version, bool is_request>
class message {
    using header_type = ztech::zp::message_header<version, is_request>;

  public:
    message(header_type header, std::vector<std::uint8_t>&& body)
        : header_{header}, body_{std::move(body)} {
        assert(header_.body_length == body_.size());
    }

    [[nodiscard]] inline auto header() const noexcept -> const header_type& {
        return header_;
    }

    [[nodiscard]] inline auto body() const noexcept
        -> const std::vector<std::uint8_t>& {
        return body_;
    }

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

template <std::uint8_t version>
using request = message<version, true>;

template <std::uint8_t version>
using response = message<version, false>;

} // namespace ztech::zp

#endif
