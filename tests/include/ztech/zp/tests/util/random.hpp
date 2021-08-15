#ifndef ZTECH_ZP_TESTS_UTIL_RANDOM_HPP
#define ZTECH_ZP_TESTS_UTIL_RANDOM_HPP

#include <algorithm>
#include <cstddef>
#include <limits>
#include <random>
#include <string>
#include <type_traits>

namespace ztech::zp::tests::util {

enum class random_string_options : std::uint32_t {
    alpha      = 1U << 0U,
    num        = 1U << 1U,
    sym        = 1U << 2U,
    lower_case = 1U << 3U,
    upper_case = 1U << 4U,
    alphanum   = alpha | num,
    mixed_case = lower_case | upper_case,
    mixed      = alpha | num | lower_case | upper_case | sym,
};

inline auto operator&(random_string_options lhs, random_string_options rhs) {
    return static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs);
}

inline auto operator|(random_string_options lhs, random_string_options rhs) {
    return static_cast<random_string_options>(static_cast<std::uint32_t>(lhs) |
                                              static_cast<std::uint32_t>(rhs));
}

auto random_string(std::size_t len, random_string_options opts) -> std::string {
    std::mt19937 rng{std::random_device{}()};

    constexpr auto lower_case_alpha = "abcdefghijklmnopqrstuvwxyz";
    constexpr auto upper_case_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr auto num              = "1234567890";
    constexpr auto sym              = "`~!@#$%^&*()-_=+\"\\/?.>,<";

    std::string pool;
    std::string ret;

    if ((opts & random_string_options::alpha) != 0U) {
        if (((opts & random_string_options::lower_case) == 0U) &&
            ((opts & random_string_options::upper_case) == 0U)) {
            pool.append(lower_case_alpha);
        } else {
            if ((opts & random_string_options::lower_case) != 0U) {
                pool.append(lower_case_alpha);
            }

            if ((opts & random_string_options::upper_case) != 0U) {
                pool.append(upper_case_alpha);
            }
        }
    }

    if ((opts & random_string_options::num) != 0U) {
        pool.append(num);
    }

    if ((opts & random_string_options::sym) != 0U) {
        pool.append(sym);
    }

    std::shuffle(pool.begin(), pool.end(), rng);
    std::uniform_int_distribution<std::size_t> dist{0, pool.size() - 1};

    while ((len--) != 0U) {
        ret.push_back(pool[dist(rng)]);
    }

    return ret;
}

template <typename T>
requires std::is_integral_v<T> || std::is_floating_point_v<T>
auto random(T min = std::numeric_limits<T>::min(),
            T max = std::numeric_limits<T>::max()) -> T {
    std::mt19937 rng{std::random_device{}()};

    if constexpr (std::is_integral_v<T>) {
        return std::uniform_int_distribution<T>{min, max}(rng);
    } else {
        return std::uniform_real_distribution<T>{min, max}(rng);
    }
}

template <typename T, std::size_t count>
requires std::is_integral_v<T> || std::is_floating_point_v<T>
auto random_vector() -> std::vector<T> {
    std::vector<T> ret{};

    for (std::size_t i{0}; i < count; ++i) {
        ret.emplace_back(random<T>());
    }

    return ret;
}

} // namespace ztech::zp::tests::util

#endif
