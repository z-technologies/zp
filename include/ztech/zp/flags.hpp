#ifndef ZTECH_ZP_FLAGS_HPP
#define ZTECH_ZP_FLAGS_HPP

#include <cstdint>
#include <type_traits>

namespace ztech::zp {
inline namespace v1 {

enum class flags : std::uint16_t {
    none                 = 0,
    end_of_conversation  = 1 << 0,
    terminate_connection = 1 << 1,
    checksum             = 1 << 2,
    ack                  = 1 << 3,
    compress             = 1 << 4,
};

}

inline auto operator|(const flags &rhs, const flags &lhs) -> flags {
    return static_cast<flags>(static_cast<std::uint16_t>(rhs) |
                              static_cast<std::uint16_t>(lhs));
}

inline auto operator&(const flags &rhs, const flags &lhs) -> flags {
    return static_cast<flags>(static_cast<std::uint16_t>(rhs) &
                              static_cast<std::uint16_t>(lhs));
}

inline auto operator^(const flags &rhs, const flags &lhs) -> flags {
    return static_cast<flags>(static_cast<std::uint16_t>(rhs) ^
                              static_cast<std::uint16_t>(lhs));
}

inline auto operator|=(flags &rhs, const flags &lhs) -> flags & {
    rhs = rhs | lhs;
    return rhs;
}

inline auto operator&=(flags &rhs, const flags &lhs) -> flags & {
    rhs = rhs & lhs;
    return rhs;
}

inline auto operator^=(flags &rhs, const flags &lhs) -> flags & {
    rhs = rhs ^ lhs;
    return rhs;
}

} // namespace ztech::zp

#endif
