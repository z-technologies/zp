#ifndef ZTECH_ZP_FLAGS_HPP
#define ZTECH_ZP_FLAGS_HPP

#include <cstdint>
#include <type_traits>

namespace ztech::zp {
inline namespace v1 {

enum class flags : std::uint16_t {
    none                 = 0x0000,
    end_of_conversation  = 0x0001,
    terminate_connection = 0x0002,
    checksum             = 0x0004,
    ack                  = 0x0008
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
