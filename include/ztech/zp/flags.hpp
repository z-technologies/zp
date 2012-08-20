#ifndef ZTECH_ZP_FLAGS_HPP
#define ZTECH_ZP_FLAGS_HPP

#include <cstdint>

namespace ztech::zp {

using flags_underlying_type = std::uint8_t;

enum class flags : flags_underlying_type {
    none       = 0U,
    is_request = 1U << 0U,
};

inline auto operator|(const flags& rhs, const flags& lhs) -> flags {
    return static_cast<flags>(static_cast<std::uint16_t>(rhs) |
                              static_cast<std::uint16_t>(lhs));
}

inline auto operator&(const flags& rhs, const flags& lhs) -> flags {
    return static_cast<flags>(static_cast<std::uint16_t>(rhs) &
                              static_cast<std::uint16_t>(lhs));
}

inline auto operator^(const flags& rhs, const flags& lhs) -> flags {
    return static_cast<flags>(static_cast<std::uint16_t>(rhs) ^
                              static_cast<std::uint16_t>(lhs));
}

inline auto operator|=(flags& rhs, const flags& lhs) -> flags& {
    rhs = rhs | lhs;
    return rhs;
}

inline auto operator&=(flags& rhs, const flags& lhs) -> flags& {
    rhs = rhs & lhs;
    return rhs;
}

inline auto operator^=(flags& rhs, const flags& lhs) -> flags& {
    rhs = rhs ^ lhs;
    return rhs;
}

inline auto operator~(const flags& lhs) -> flags {
    return static_cast<flags>(~static_cast<std::uint16_t>(lhs));
}

} // namespace ztech::zp

#endif
