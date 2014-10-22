cmake_minimum_required(VERSION 2.8)

IF(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     SET(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
ENDIF()

project(soft-renderer)
SET(CMAKE_BUILD_TYPE Debug)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -fopenmp")

# for glm
add_definitions(-DGLM_FORCE_RADIANS)

add_subdirectory(src)
add_subdirectory(tests)
