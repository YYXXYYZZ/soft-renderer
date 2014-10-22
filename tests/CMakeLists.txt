project(basic_render)

IF(WIN32)
    SET(LIB_ROOT "E:/libs-dev")
    INCLUDE_DIRECTORIES("${LIB_ROOT}/inlcude" "${PROJECT_SOURCE_DIR}/../include")
    LINK_DIRECTORIES("${LIB_ROOT}/libs" "${CMAKE_BINARY_DIR}/build")
ELSE(UNIX)
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../include")
    LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/build")
ENDIF(Win32)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../build)

add_executable(${PROJECT_NAME} basic.cpp)
target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system GLEW OPENGL)

add_executable(shader-test shader-test.cpp)
target_link_libraries(shader-test sf-core)

add_executable(gpumemory-test gpumemory-test.cpp)
target_link_libraries(gpumemory-test sf-core)

add_executable(clipper-test clipper-test.cpp)
target_link_libraries(clipper-test sf-core)

add_executable(utility-test utility-test.cpp)
target_link_libraries(utility-test sf-core)

add_executable(openmp-test openmp-test.cpp)
target_link_libraries(openmp-test gomp)



