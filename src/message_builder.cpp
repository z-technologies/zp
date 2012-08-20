#include "ztech/zp/util/message_builder.hpp"

#include <cassert>
#include <cstdint>

namespace ztech::zp::util {

message_builder::message_builder(std::uint16_t type, std::uint16_t command,
                                 std::vector<std::uint8_t> body)
    : header_{.type        = type,
              .command     = command,
              .flags       = ztech::zp::flags::none,
              .tag         = next_tag(),
              .body_length = 0U},
      body_{std::move(body)} {
}

message_builder::message_builder(std::uint16_t type, std::uint16_t command)
    : message_builder{type, command, {}} {
}

message_builder::message_builder() : message_builder{0, 0} {
}

auto message_builder::with_type(std::uint16_t type) noexcept
    -> message_builder& {
    header_.type = type;
    return *this;
}

auto message_builder::with_command(std::uint16_t command) noexcept
    -> message_builder& {
    header_.command = command;
    return *this;
}

auto message_builder::with_tag(std::uint32_t tag) noexcept -> message_builder& {
    header_.tag = tag;
    return *this;
}

auto message_builder::with_flags(ztech::zp::flags flags) noexcept
    -> message_builder& {
    header_.flags = flags;
    return *this;
}

auto message_builder::with_body(const std::vector<std::uint8_t>& body) noexcept
    -> message_builder& {
    assert(body.size() <= ztech::zp::message_header::max_body_length);

    body_               = body;
    header_.body_length = body_.size();

    return *this;
}

auto message_builder::with_body(std::vector<std::uint8_t>&& body) noexcept
    -> message_builder& {
    assert(body.size() <= ztech::zp::message_header::max_body_length);

    body_               = std::move(body);
    header_.body_length = body_.size();

    return *this;
}

auto message_builder::build() noexcept -> ztech::zp::message {
    return {header_, std::move(body_)};
}

} // namespace ztech::zp::util
