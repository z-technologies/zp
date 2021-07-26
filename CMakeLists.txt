cmake_minimum_required(VERSION 3.10)

# project name
project(zp LANGUAGES CXX)

# project options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project files
set(SOURCE_FILES src/dummy.cpp)
set(HEADER_FILES include/ztech/zp/message.hpp
                 include/ztech/zp/flags.hpp)
include_directories(include/)

# targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

# external dependencies
add_definitions(-DMSGPACK_USE_BOOST)
add_subdirectory(lib/msgpack-c/)

target_link_libraries(${PROJECT_NAME} msgpack)
