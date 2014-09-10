set(INCROOT ${PROJECT_SOURCE_DIR}/include/core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/core)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC
    ${INCROOT}/culler.h
    ${SRCROOT}/culler.cpp
    ${INCROOT}/global.h
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
    ${SRCROOT}/sutherlandhodgmanclipper.cpp
    ${INCROOT}/sutherlandhodgmanclipper.h
)
SET(BUILD_SHARED_LIBS ON)
source_group("" FILES ${SRC})
add_library(sf-core ${SRC})
