project(dcdr-interconnect)


file(GLOB DCDR_INTERCONNECT_INCLUDES include/dcdr/messaging/*.h)

set(DCDR_INTERCONNECT_INCLUDES
        ${DCDR_INTERCONNECT_INCLUDES}

        src/serialization/FlatBuffers.h)

file(GLOB DCDR_INTERCONNECT_SOURCES src/messaging/*.cpp)

set(SOURCE_FILES ${DCDR_INTERCONNECT_INCLUDES} ${DCDR_INTERCONNECT_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${FlatBuffers_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common)