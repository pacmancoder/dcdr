project(dcdr-server)

set(DCDR_SERVER_INCLUDES
        src/webserver/WebServerExceptions.h)

set(DCDR_SERVER_SOURCES
        src/main.cpp src/webserver/WebServer.cpp src/webserver/WebServer.h)


set(SOURCE_FILES ${DCDR_SERVER_INCLUDES} ${DCDR_SERVER_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE mongoose)

target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-logger)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-interconnect)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)