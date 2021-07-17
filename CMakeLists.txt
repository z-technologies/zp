cmake_minimum_required(VERSION 3.10)

# project name
project(zp LANGUAGES CXX)

# project options
set(CMAKE_CXX_STANDARD 17)

# project files
set(SOURCE_FILES)
set(HEADER_FILES)

# targets
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
