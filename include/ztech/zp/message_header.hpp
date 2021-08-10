#ifndef ZTECH_ZP_MESSAGE_HEADER_HPP
#define ZTECH_ZP_MESSAGE_HEADER_HPP

#include "ztech/zp/flags.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace ztech::zp {

struct message_header {
    static constexpr std::size_t size{15UL};
    static constexpr std::size_t max_body_length{
        std::numeric_limits<std::uint32_t>::max()};

    std::uint8_t     version;
    std::uint16_t    type;
    std::uint16_t    command;
    ztech::zp::flags flags;
    std::uint32_t    tag;
    std::uint32_t    body_length;

    void encode(std::array<std::uint8_t, size>& buf) const noexcept;
    void encode(std::vector<std::uint8_t>& buf) const noexcept;

    [[nodiscard]] inline auto is_request() const noexcept -> bool {
        return (version & 1U) == 1U;
    }

    static_assert(size == (sizeof(version) + sizeof(type) + sizeof(command) +
                           sizeof(tag) + sizeof(flags) + sizeof(body_length)));
};

} // namespace ztech::zp

#endif
