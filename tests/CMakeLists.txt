project(basic_render)

link_directories("${CMAKE_BINARY_DIR}/lib")
include_directories("${PROJECT_SOURCE_DIR}/../include")

add_executable(${PROJECT_NAME} basic.cpp)

IF(WIN32)
    target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system GLEW32 OPENGL32)
ENDIF(WIN32)

IF(UNIX)
    target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system GLEW GL)
ENDIF(UNIX)

add_executable(shader-test shader-test.cpp)
target_link_libraries(shader-test sf-core)

add_executable(gpumemory-test gpumemory-test.cpp)
target_link_libraries(gpumemory-test sf-core)

add_executable(clipper-test clipper-test.cpp)
target_link_libraries(clipper-test sf-core)

add_executable(utility-test utility-test.cpp)
target_link_libraries(utility-test sf-core)


