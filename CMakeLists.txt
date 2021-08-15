cmake_minimum_required(VERSION 3.10)

# project name
project(zp LANGUAGES CXX)
set(MAIN_PROJECT_NAME ${PROJECT_NAME})

# project options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project files
include_directories(include/)

## external dependencies
# boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})
# msgpack
add_definitions(-DMSGPACK_USE_BOOST -DMSGPACK_BUILD_EXAMPLES=OFF -DMSGPACK_CXX17)
add_subdirectory(lib/msgpack-c)
# googletest
add_subdirectory(lib/googletest)

# targets
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} PUBLIC INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE msgpackcxx)

# testing
enable_testing()
add_subdirectory(tests)
