project(basic_render)
SET(CMAKE_BUILD_TYPE Debug)

link_directories("${PROJECT_SOURCE_DIR}/../lib")
include_directories("${PROJECT_SOURCE_DIR}/../include")

add_executable(${PROJECT_NAME} basic.cpp)
target_link_libraries(${PROJECT_NAME} sf-core sfml-graphics sfml-window sfml-system)

add_executable(warehouse-test warehouse-test.cpp)
target_link_libraries(warehouse-test sf-core)
