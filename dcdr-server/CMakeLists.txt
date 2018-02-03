project(dcdr-server)

file(GLOB DCDR_SERVER_CORE_INCLUDES                    include/dcdr/server/core/*.h)
file(GLOB DCDR_SERVER_TRANSPORT_INCLUDES                    include/dcdr/server/transport/*.h)
file(GLOB DCDR_SERVER_TRANSPORT_MONGOOSE_COMMON_INCLUDES    include/dcdr/server/transport/mongoose-common/*.h)
file(GLOB DCDR_SERVER_TRANSPORT_MONGOOSE_TCP_INCLUDES       include/dcdr/server/transport/mongoose-tcp/*.h)
file(GLOB DCDR_SERVER_TRANSPORT_MONGOOSE_WEBSOCKET_INCLUDES include/dcdr/server/transport/mongoose-websocket/*.h)

set(DCDR_SERVER_INCLUDES
        ${DCDR_SERVER_CORE_INCLUDES}
        ${DCDR_SERVER_TRANSPORT_INCLUDES}
        ${DCDR_SERVER_TRANSPORT_MONGOOSE_COMMON_INCLUDES}
        ${DCDR_SERVER_TRANSPORT_MONGOOSE_TCP_INCLUDES}
        ${DCDR_SERVER_TRANSPORT_MONGOOSE_WEBSOCKET_INCLUDES})

file(GLOB DCDR_SERVER_CORE_SOURCES                         src/server/core/*.cpp)
file(GLOB DCDR_SERVER_TRANSPORT_SOURCES                    src/server/transport/*.cpp)
file(GLOB DCDR_SERVER_TRANSPORT_MONGOOSE_COMMON_SOURCES    src/server/transport/mongoose-common/*.cpp)
file(GLOB DCDR_SERVER_TRANSPORT_MONGOOSE_TCP_SOURCES       src/server/transport/mongoose-tcp/*.cpp)
file(GLOB DCDR_SERVER_TRANSPORT_MONGOOSE_WEBSOCKET_SOURCES src/server/transport/mongoose-websocket/*.cpp)


set(DCDR_SERVER_SOURCES
        ${DCDR_SERVER_CORE_SOURCES}
        ${DCDR_SERVER_TRANSPORT_SOURCES}
        ${DCDR_SERVER_TRANSPORT_MONGOOSE_COMMON_SOURCES}
        ${DCDR_SERVER_TRANSPORT_MONGOOSE_TCP_SOURCES}
        ${DCDR_SERVER_TRANSPORT_MONGOOSE_WEBSOCKET_SOURCES}
        src/main.cpp)


set(SOURCE_FILES
        ${DCDR_SERVER_INCLUDES}
        ${DCDR_SERVER_SOURCES})

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE mongoose)

target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-logger)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-interconnect)

if (NOT WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()