#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/flags.hpp"

#include <cstdint>

namespace ztech::zp {
inline namespace v1 {

constexpr std::uint8_t protocol_version{0x00};

struct message_header {
    std::uint8_t         version;
    std::uint16_t        type;
    std::uint16_t        command;
    std::uint16_t        tag;
    ztech::zp::v1::flags flags;
    std::uint16_t        body_length;
};

} // namespace v1
} // namespace ztech::zp

#endif
