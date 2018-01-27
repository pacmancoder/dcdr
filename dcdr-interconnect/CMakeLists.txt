project(dcdr-interconnect)


file(GLOB DCDR_INTERCONNECT_COMMON_INCLUDES include/dcdr/messaging/*.h)
file(GLOB DCDR_INTERCONNECT_COMMANDER_INCLUDES include/dcdr/messaging/commander/*.h)
file(GLOB DCDR_INTERCONNECT_WORKER_INCLUDES include/dcdr/messaging/worker/*.h)
file(GLOB DCDR_INTERCONNECT_FLATBUFFERS_INCLUDES include/dcdr/messaging/flatbuffers/*.h)

set(FLATBUFFERS_INCLUDES src/serialization/FlatBuffers.h)

set(DCDR_INTERCONNECT_INCLUDES
        ${DCDR_INTERCONNECT_COMMON_INCLUDES}
        ${DCDR_INTERCONNECT_COMMANDER_INCLUDES}
        ${DCDR_INTERCONNECT_WORKER_INCLUDES}
        ${DCDR_INTERCONNECT_FLATBUFFERS_INCLUDES}
        ${FLATBUFFERS_INCLUDES})

file(GLOB DCDR_INTERCONNECT_COMMON_SOURCES src/messaging/*.cpp)
file(GLOB DCDR_INTERCONNECT_COMMANDER_SOURCES src/messaging/commander/*.cpp)
file(GLOB DCDR_INTERCONNECT_WORKER_SOURCES src/messaging/worker/*.cpp)
file(GLOB DCDR_INTERCONNECT_FLATBUFFERS_SOURCES src/messaging/flatbuffers/*.cpp)

set(SOURCE_FILES ${DCDR_INTERCONNECT_INCLUDES}
        ${DCDR_INTERCONNECT_COMMON_SOURCES}
        ${DCDR_INTERCONNECT_COMMANDER_SOURCES}
        ${DCDR_INTERCONNECT_WORKER_SOURCES}
        ${DCDR_INTERCONNECT_FLATBUFFERS_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${FlatBuffers_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common)