cmake_minimum_required(VERSION 3.10)

# project name
project(zp_tests LANGUAGES CXX)

# project files
include_directories(include/)

# project functions
function(create_test test_name)
    add_executable(${test_name} src/${test_name}_tests.cpp)
    target_link_libraries(${test_name} ${MAIN_PROJECT_NAME}
                                       gtest
                                       gtest_main)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Project targets
create_test(dummy)
create_test(testing_util_random)

create_test(serialization)
create_test(encoding)
create_test(message_header)
create_test(message_builder)
create_test(message)
create_test(compression)
