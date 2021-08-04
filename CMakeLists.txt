cmake_minimum_required(VERSION 3.10)

# project name
project(zp LANGUAGES CXX)
set(MAIN_PROJECT_NAME ${PROJECT_NAME})

# project options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project files
set(SOURCE_FILES src/message_header.cpp
                 src/message_builder.cpp)
set(HEADER_FILES include/ztech/zp/flags.hpp
                 include/ztech/zp/message_header.hpp
                 include/ztech/zp/message.hpp
                 include/ztech/zp/crc.hpp
                 include/ztech/zp/util/serialization.hpp
                 include/ztech/zp/util/message_builder.hpp)
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
# fmt
add_subdirectory(lib/fmt)

# targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} msgpackcxx fmt::fmt)

# testing
enable_testing()
add_subdirectory(tests)
