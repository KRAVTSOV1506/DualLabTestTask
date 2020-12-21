cmake_minimum_required(VERSION 3.17)
project(DualLabTestTask)

set(CMAKE_CXX_STANDARD 20)

add_executable(DualLabTestTask main.cpp SegmentTree.h SegmentTree.cpp)

add_library(catch_main
        catch/catch_main.cpp)

target_include_directories(catch_main
        PUBLIC catch)

add_executable(test SegmentTree.h SegmentTree.cpp test.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -s -O2")

target_link_libraries(test catch_main)
