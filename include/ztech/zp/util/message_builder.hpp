#ifndef ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP
#define ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP

#include "ztech/zp/message.hpp"
#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <vector>

namespace ztech::zp::util {

template <std::uint8_t version, bool is_request>
struct message_body_builder {
    explicit message_body_builder(
        ztech::zp::message_header<version, is_request> header)
        : header_{header} {
    }

    message_body_builder(ztech::zp::message_header<version, is_request> header,
                         std::vector<std::uint8_t>&&                    body)
        : header_{header}, body_{std::move(body)} {
    }

    [[nodiscard]] inline auto build()
        -> ztech::zp::message<version, is_request> {
        header_.body_length = body_.size();
        return {header_, std::move(body_)};
    }

  private:
    ztech::zp::message_header<version, is_request> header_{};
    std::vector<std::uint8_t>                      body_;
};

template <std::uint8_t version, bool is_request>
struct message_header_builder {
    message_header_builder(std::uint16_t type, std::uint16_t extra,
                           std::uint32_t tag)
        : header_{.type = type, .extra = extra, .tag = tag, .body_length = 0U} {
    }

    [[nodiscard]] inline auto with_body(std::vector<std::uint8_t> body)
        -> message_body_builder<version, is_request> {
        return message_body_builder<version, is_request>{header_,
                                                         std::move(body)};
    }

    [[nodiscard]] inline auto with_body(std::vector<std::uint8_t>&& body)
        -> message_body_builder<version, is_request> {
        return message_body_builder<version, is_request>{header_,
                                                         std::move(body)};
    }

  private:
    ztech::zp::message_header<version, is_request> header_{};
};

template <std::uint8_t version, bool is_request, typename... Arg>
[[nodiscard]] auto make_message_builder(Arg&&... args) {
    return message_header_builder<version, true>(std::forward<Arg>(args)...);
}

template <std::uint8_t version>
[[nodiscard]] auto make_request_builder(std::uint16_t type, std::uint16_t extra,
                                        std::uint32_t tag) {
    return make_message_builder<version, true>(type, extra, tag);
}

template <std::uint8_t version>
[[nodiscard]] auto
make_response_builder(const ztech::zp::request<version>& req) {
    return make_message_builder<version, false>(
        req.header().type, req.header().extra, req.header().tag);
}

} // namespace ztech::zp::util

#endif
