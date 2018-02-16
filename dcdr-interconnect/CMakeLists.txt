project(dcdr-interconnect)

add_subdirectory(flatbuffers)

file(GLOB DCDR_INTERCONNECT_COMMON_INCLUDES include/dcdr/messaging/*.h)
file(GLOB DCDR_INTERCONNECT_COMMANDER_INCLUDES include/dcdr/messaging/commander/*.h)
file(GLOB DCDR_INTERCONNECT_WORKER_INCLUDES include/dcdr/messaging/worker/*.h)
file(GLOB DCDR_INTERCONNECT_FLATBUFFERS_INCLUDES include/dcdr/messaging/flatbuffers/*.h)
file(GLOB DCDR_INTERCONNECT_FLATBUFFERS_INCLUDES_GENERATED ${CMAKE_BINARY_DIR}/gen/flatbuffers/cpp/*.h)

set(DCDR_INTERCONNECT_INCLUDES
        ${DCDR_INTERCONNECT_COMMON_INCLUDES}
        ${DCDR_INTERCONNECT_COMMANDER_INCLUDES}
        ${DCDR_INTERCONNECT_WORKER_INCLUDES}
        ${DCDR_INTERCONNECT_FLATBUFFERS_INCLUDES}
        ${DCDR_INTERCONNECT_FLATBUFFERS_INCLUDES_GENERATED}
        ${FLATBUFFERS_INCLUDES})

file(GLOB DCDR_INTERCONNECT_COMMON_SOURCES src/messaging/*.cpp)
file(GLOB DCDR_INTERCONNECT_COMMANDER_SOURCES src/messaging/commander/*.cpp)
file(GLOB DCDR_INTERCONNECT_WORKER_SOURCES src/messaging/worker/*.cpp)
file(GLOB DCDR_INTERCONNECT_FLATBUFFERS_SOURCES src/messaging/flatbuffers/*.cpp)
file(GLOB DCDR_INTERCONNECT_FLATBUFFERS_PRIVATE_SOURCES src/messaging/flatbuffers/private/*.cpp)

set(SOURCE_FILES ${DCDR_INTERCONNECT_INCLUDES}
        ${DCDR_INTERCONNECT_COMMON_SOURCES}
        ${DCDR_INTERCONNECT_COMMANDER_SOURCES}
        ${DCDR_INTERCONNECT_WORKER_SOURCES}
        ${DCDR_INTERCONNECT_FLATBUFFERS_SOURCES}
        ${DCDR_INTERCONNECT_FLATBUFFERS_PRIVATE_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${FlatBuffers_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/gen/flatbuffers/cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC dcdr-common)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-logger)
add_dependencies(${PROJECT_NAME} dcdr-interconnect-flatbuffers)