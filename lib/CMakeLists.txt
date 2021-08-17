cmake_minimum_required(VERSION 3.10)

# boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

# msgpack
add_definitions(-DMSGPACK_USE_BOOST
                -DMSGPACK_BUILD_EXAMPLES=OFF
                -DMSGPACK_CXX17)
add_subdirectory(msgpack-c)
add_library(zp::msgpack ALIAS msgpackcxx)

# googletest
add_subdirectory(googletest)
add_library(zp::gtest ALIAS gtest)
add_library(zp::gtest_main ALIAS gtest_main)

# zstd
add_subdirectory(zstd/build/cmake)
add_library(zp::zstd ALIAS libzstd_static)

# lz4
add_subdirectory(lz4/build/cmake)
add_library(zp::lz4 ALIAS lz4_static)
