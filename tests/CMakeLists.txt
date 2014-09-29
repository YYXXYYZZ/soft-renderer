project(basic_render)

link_directories("${PROJECT_SOURCE_DIR}/../lib")
include_directories("${PROJECT_SOURCE_DIR}/../include")

add_executable(${PROJECT_NAME} basic.cpp)
target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system GLEW GL)

add_executable(shader-test shader-test.cpp)
target_link_libraries(shader-test sf-core)

add_executable(gpumemory-test gpumemory-test.cpp)
target_link_libraries(gpumemory-test sf-core)

add_executable(clipper-test clipper-test.cpp)
target_link_libraries(clipper-test sf-core)

add_executable(utility-test utility-test.cpp)
target_link_libraries(utility-test sf-core)


