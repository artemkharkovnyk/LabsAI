cmake_minimum_required(VERSION 3.2)

project(lab2)

add_library(gen STATIC src/gen.cpp)

add_executable(test src/testcase.cpp)

target_link_libraries(test PRIVATE gen)

set_target_properties(test
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
