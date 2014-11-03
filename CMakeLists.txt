cmake_minimum_required(VERSION 2.8)

IF(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     SET(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
ENDIF()

project(soft-renderer)
SET(CMAKE_BUILD_TYPE Debug)

if(MSVC)
    message(STATUS "Building with visual c++...")
    set (GRAPHIC_SDK "E:/SDK/graphics/vc")
else()
    message(STATUS "Building with gcc...")
    list( APPEND CMAKE_CXX_FLAGS "-std=c++11")
endif(MSVC)

find_package(OpenMP)
if(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_subdirectory(src)
add_subdirectory(tests)
