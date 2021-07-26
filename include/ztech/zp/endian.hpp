#ifndef ZTECH_ZP_ENDIAN_HPP
#define ZTECH_ZP_ENDIAN_HPP

#include <type_traits>
#include <bit>

namespace ztech::zp {

constexpr auto is_network_ordering() -> bool {
    return std::endian::native == std::endian::big;
}

template <typename T>
requires std::is_integral_v<T>
constexpr auto host_to_network(T value) -> T {
    if constexpr (is_network_ordering()) {
        return value;
    }

    T ret{};

    for (std::size_t i{0}; i < sizeof(T); ++i) {
        ret <<= 8;
        ret |= (value >> 8 * i) & 0xFF;
    }

    return ret;
}

} // namespace ztech::zp

#endif
