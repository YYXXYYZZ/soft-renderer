set(INCROOT ${PROJECT_SOURCE_DIR}/include/core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/core)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${SRCROOT}/shader.cpp
    ${INCROOT}/shader.h
    ${SRCROOT}/vertexshader.cpp
    ${INCROOT}/vertexshader.h
)
SET(BUILD_SHARED_LIBS ON)
source_group("" FILES ${SRC})
add_library(sf-core ${SRC})
