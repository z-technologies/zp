#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/flags.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace ztech::zp::inline v1 {

constexpr std::uint8_t protocol_version{0x00};

struct message_header {
    static constexpr std::size_t size{16UL};
    static constexpr std::size_t max_body_length{
        std::numeric_limits<std::uint32_t>::max()};

    std::uint8_t         version;
    std::uint16_t        type;
    std::uint16_t        command;
    ztech::zp::v1::flags flags;
    std::uint32_t        tag;
    std::uint32_t        body_length;
    std::uint8_t         header_checksum;

    void update_checksum() noexcept;
    void encode(std::array<std::uint8_t, size>& buf) noexcept;
};

static_assert(message_header::size ==
              (sizeof(std::declval<message_header>().version) +
               sizeof(std::declval<message_header>().type) +
               sizeof(std::declval<message_header>().command) +
               sizeof(std::declval<message_header>().tag) +
               sizeof(std::declval<message_header>().flags) +
               sizeof(std::declval<message_header>().body_length) +
               sizeof(std::declval<message_header>().header_checksum)));

} // namespace ztech::zp::inline v1

#endif
