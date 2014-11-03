include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${GRAPHIC_SDK}/include")

set(INCROOT ${PROJECT_SOURCE_DIR}/include/core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/core)

set(SRC
    ${INCROOT}/vertex.h
    ${SRCROOT}/vertex.cpp
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
    ${SRCROOT}/fragshader.cpp
    ${INCROOT}/fragshader.h
    ${INCROOT}/constant.h
)
source_group("" FILES ${SRC})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

add_library(sf-core-shared SHARED ${SRC})
add_library(sf-core-static STATIC ${SRC})

if(MSVC)
else()
    target_link_libraries(sf-core gomp)
endif(MSVC)

