#ifndef ZTECH_ZP_FLAGS_HPP
#define ZTECH_ZP_FLAGS_HPP

#include <cstdint>

namespace ztech::zp {
inline namespace v1 {

enum class flags : std::uint16_t {
    none           = 0,
    end_of_message = 1U << 0U,
    end_of_stream  = 1U << 1U,
    end_of_session = 1U << 2U,
    has_checksum   = 1U << 3U,
    requires_ack   = 1U << 4U,
};

}

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
