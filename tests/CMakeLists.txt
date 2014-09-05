project(basic_render)

link_directories("${PROJECT_SOURCE_DIR}/../lib")
include_directories("${PROJECT_SOURCE_DIR}/../include")

add_executable(${PROJECT_NAME} basic.cpp)
target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system)

add_executable(shader-test shader-test.cpp)
target_link_libraries(shader-test sf-core)
