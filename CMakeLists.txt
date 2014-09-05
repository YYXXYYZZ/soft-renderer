cmake_minimum_required(VERSION 2.8)

project(soft-renderer)
SET(CMAKE_BUILD_TYPE Debug)
list( APPEND CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory(src)
add_subdirectory(tests)
