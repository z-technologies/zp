cmake_minimum_required(VERSION 3.10)

# project name
project(zp LANGUAGES CXX)
set(MAIN_PROJECT_NAME ${PROJECT_NAME})

# project options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project files
set(SOURCE_FILES src/compress_zstd.cpp)
include_directories(include/)

# external dependencies
add_subdirectory(lib)
include_directories(${Boost_INCLUDE_DIR}
                    lib/zstd/lib/) # workaround to add lib directory for zstd

# targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} zp::msgpack
                                      zp::zstd
                                      zp::lz4)

# testing
enable_testing()
add_subdirectory(tests)
