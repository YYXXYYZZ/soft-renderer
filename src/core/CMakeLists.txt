set(INCROOT ${PROJECT_SOURCE_DIR}/include/core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/core)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${INCROOT}/buffer.h
    ${SRCROOT}/buffer.cpp
    ${INCROOT}/zbuffer.h
    ${SRCROOT}/zbuffer.cpp
    ${INCROOT}/primitive.h
    ${SRCROOT}/primitive.cpp
    ${INCROOT}/culler.h
    ${SRCROOT}/culler.cpp
    ${SRCROOT}/shader.cpp
    ${INCROOT}/shader.h
    ${SRCROOT}/vertexshader.cpp
    ${INCROOT}/vertexshader.h
    ${SRCROOT}/gpumemory.cpp
    ${INCROOT}/gpumemory.h
    ${SRCROOT}/pipeline.cpp
    ${INCROOT}/pipeline.h
    ${SRCROOT}/clipper.cpp
    ${INCROOT}/clipper.h
    ${SRCROOT}/sh-clipper.cpp
    ${INCROOT}/sh-clipper.h
    ${INCROOT}/constant.h
)
SET(BUILD_SHARED_LIBS ON)
source_group("" FILES ${SRC})
add_library(sf-core ${SRC})
