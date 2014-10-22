IF(WIN32)
    SET(LIB_ROOT "E:/libs-dev")
    INCLUDE_DIRECTORIES("${LIB_ROOT}/inlcude" "${PROJECT_SOURCE_DIR}/inlcude")
ELSE(UNIX)
    include_directories("${PROJECT_SOURCE_DIR}/inlcude")
ENDIF(Win32)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/build)

add_subdirectory(core)
