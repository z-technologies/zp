#ifndef ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP
#define ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP

#include "ztech/zp/message.hpp"
#include "ztech/zp/message_header.hpp"
#include "ztech/zp/util/serialization.hpp"

#include <atomic>
#include <cassert>
#include <cstdint>
#include <vector>

namespace ztech::zp::util {

template <std::uint8_t version, bool is_request>
struct message_body_builder {
    explicit message_body_builder(
        ztech::zp::message_header<version, is_request> header)
        : header_{std::move(header)} {
    }

    message_body_builder(ztech::zp::message_header<version, is_request> header,
                         std::vector<std::uint8_t>&&                    body)
        : header_{std::move(header)}, body_{std::move(body)} {
    }

    [[nodiscard]] inline auto build()
        -> ztech::zp::message<version, is_request> {
        return {std::move(header_), std::move(body_)};
    }

  private:
    ztech::zp::message_header<version, is_request> header_{};
    std::vector<std::uint8_t>                      body_;
};

template <std::uint8_t version, bool is_request>
struct message_header_builder {
    message_header_builder(std::uint16_t type, std::uint16_t command,
                           std::uint32_t tag)
        : header_{
              .type = type, .command = command, .tag = tag, .body_length = 0U} {
    }

    template <typename BodyContainer>
    [[nodiscard]] auto with_body(BodyContainer&& body)
        -> message_body_builder<version, is_request> {
        return message_body_builder<version, is_request>{
            std::move(header_), std::forward<BodyContainer>(body)};
    }

  private:
    ztech::zp::message_header<version, is_request> header_{};
};

template <std::uint8_t version>
[[nodiscard]] auto make_request_builder(std::uint16_t type,
                                        std::uint16_t command,
                                        std::uint32_t tag) {
    return message_header_builder<version, true>(type, command, tag);
}

template <std::uint8_t version>
[[nodiscard]] auto
make_response_builder(const ztech::zp::request<version>& req) {
    return message_header_builder<version, false>(
        req.header().type, req.header().command, req.header().tag);
}

} // namespace ztech::zp::util

#endif
