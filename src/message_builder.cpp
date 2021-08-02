#include "ztech/zp/util/message_builder.hpp"

namespace ztech::zp::v1 {

message_builder::message_builder(std::uint16_t type, std::uint16_t command)
    : header_{.version     = ztech::zp::v1::protocol_version,
              .type        = type,
              .command     = command,
              .tag         = next_tag(),
              .flags       = ztech::zp::flags::none,
              .body_length = 0U} {
}
auto message_builder::with_version(std::uint8_t version) noexcept
    -> message_builder& {
    header_.version = version;
    return *this;
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

auto message_builder::with_tag(std::uint16_t tag) noexcept -> message_builder& {
    header_.tag = tag;
    return *this;
}
auto message_builder::with_flags(ztech::zp::v1::flags flags) noexcept
    -> message_builder& {
    header_.flags = flags;
    return *this;
}

auto message_builder::end_of_message() noexcept -> message_builder& {
    header_.flags |= ztech::zp::v1::flags::end_of_message;
    return *this;
}

auto message_builder::end_of_stream() noexcept -> message_builder& {
    header_.flags |= ztech::zp::v1::flags::end_of_stream;
    return *this;
}

auto message_builder::end_of_session() noexcept -> message_builder& {
    header_.flags |= ztech::zp::v1::flags::end_of_session;
    return *this;
}

auto message_builder::require_ack() noexcept -> message_builder& {
    header_.flags |= ztech::zp::v1::flags::requires_ack;
    return *this;
}

auto message_builder::include_checksum() noexcept -> message_builder& {
    header_.flags |= ztech::zp::v1::flags::has_checksum;
    return *this;
}

} // namespace ztech::zp::v1
