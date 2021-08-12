#include "ztech/zp/tests/util/random.hpp"

#include "gtest/gtest.h"

#include <algorithm>
#include <cctype>
#include <string>

using namespace ztech::zp::tests::util;

namespace {

constexpr auto test_container_size = 0xFF;

template <typename T>
void test_vector() {
    auto vec = random_vector<T, test_container_size>();
    EXPECT_EQ(vec.size(), test_container_size);
    EXPECT_FALSE(std::all_of(std::cbegin(vec), std::cend(vec),
                             [&vec](auto c) { return c == vec[0]; }));
};

} // namespace

namespace tikpp::tests {

TEST(UtilRandomTests, NumOnlyTest) { // !NOLINT
    auto str = random_string(::test_container_size, random_string_options::num);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(),
                            [](auto c) { return std::isdigit(c); }));
}

TEST(UtilRandomTests, AlphaTest) { // !NOLINT
    auto str =
        random_string(::test_container_size, random_string_options::alpha);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(),
                            [](auto c) { return std::isalpha(c); }));
}

TEST(UtilRandomTests, LowerAlphaTest) { // !NOLINT
    auto str = random_string(::test_container_size,
                             random_string_options::alpha |
                                 random_string_options::lower_case);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(), [](auto c) {
        return std::isalpha(c) && std::islower(c);
    }));
}

TEST(UtilRandomTests, UpperAlphaTest) { // !NOLINT
    auto str = random_string(::test_container_size,
                             random_string_options::alpha |
                                 random_string_options::upper_case);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(), [](auto c) {
        return std::isalpha(c) && std::isupper(c);
    }));
}

TEST(UtilRandomTests, MixedAlphaTest) { // !NOLINT
    auto str = random_string(::test_container_size,
                             random_string_options::alpha |
                                 random_string_options::mixed_case);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(), [](auto c) {
        return std::isalpha(c) && (std::islower(c) || std::isupper(c));
    }));
}

TEST(UtilRandomTests, AlphaNumTest) { // !NOLINT
    auto str =
        random_string(::test_container_size, random_string_options::alphanum);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(),
                            [](auto c) { return std::isalnum(c); }));
}

TEST(UtilRandomTests, SymboleTest) { // !NOLINT
    auto str = random_string(::test_container_size, random_string_options::sym);

    EXPECT_EQ(str.size(), ::test_container_size);
    EXPECT_TRUE(std::all_of(str.begin(), str.end(),
                            [](auto c) { return !std::isalnum(c); }));
}

TEST(UtilRandomTests, MixedTest) { // !NOLINT
    auto str =
        random_string(::test_container_size, random_string_options::mixed);
    EXPECT_EQ(str.size(), ::test_container_size);
}

TEST(UtilRandomTests, IntTest) { // !NOLINT
    constexpr auto min = 1;
    constexpr auto max = 100;

    auto value = random<int>(min, max);

    EXPECT_GE(value, min);
    EXPECT_LE(value, max);
}

TEST(UtilRandomTests, DoubleTest) { // !NOLINT
    constexpr auto min = 1.0;
    constexpr auto max = 100.0;

    auto value = random<double>(min, max);

    EXPECT_GE(value, min);
    EXPECT_LE(value, max);
}

TEST(UtilRandomTests, LongTest) { // !NOLINT
    constexpr auto min = 1UL;
    constexpr auto max = 100UL;

    auto value = random<long>(min, max);

    EXPECT_GE(value, min);
    EXPECT_LE(value, max);
}

TEST(UtilRandomTests, RandomVectorTest) { // !NOLINT
    test_vector<std::uint8_t>();
    test_vector<std::uint16_t>();
    test_vector<std::uint32_t>();
    test_vector<std::uint64_t>();
    test_vector<float>();
    test_vector<double>();
}

} // namespace tikpp::tests
