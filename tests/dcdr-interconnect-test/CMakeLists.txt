project(dcdr-interconnect-test)

file(GLOB DCDR_INTERCONNECT_TEST_SOURCES *.cpp)

add_executable(
        ${PROJECT_NAME}
        ${DCDR_INTERCONNECT_TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE test-utils)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-interconnect)