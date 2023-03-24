cmake_minimum_required(VERSION 3.2)

project(labTestCase)

add_library(graph graph.cpp)

add_executable(testcase testcase.cpp)

target_link_libraries(testcase graph)

set_target_properties(testcase PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
