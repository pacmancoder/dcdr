project(dcdr-server-test)

file(GLOB SOURCES_SERVER_TEST *.cpp)

add_executable(
        ${PROJECT_NAME}
        ${SOURCES_SERVER_TEST})

add_test(NAME DcdrServerTest COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE test-utils)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-server)