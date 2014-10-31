project(basic_render)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../include")
LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/build")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../build)

add_executable(${PROJECT_NAME} basic.cpp)
target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system GLEW GL)

add_executable(model-test model-test.cpp)
target_link_libraries(model-test sf-core glfw3 gl)

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



