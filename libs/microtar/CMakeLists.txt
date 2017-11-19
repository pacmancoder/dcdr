project(microtar)

SET(MICROTAR_DIR microtar-0.1)

SET(MICROTAR_SOURCES
        ${MICROTAR_DIR}/src/microtar.c)

SET(MICROTAR_HEADERS
        ${MICROTAR_DIR}/src/microtar.h)

include_directories(${MICROTAR_DIR}/src)

add_library(${PROJECT_NAME} STATIC
        ${MICROTAR_SOURCES}
        ${MICROTAR_HEADERS})

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} PUBLIC ${MICROTAR_DIR}/src)