project(dcdr-interconnect-test)

file(GLOB DCDR_INTERCONNECT_TEST_SOURCES *.cpp)
file(GLOB DCDR_INTERCONNECT_TEST_FLATBUFFERS_SOURCES flatbuffers/*.cpp)

set(SOURCE_FILES
        ${DCDR_INTERCONNECT_TEST_SOURCES}
        ${DCDR_INTERCONNECT_TEST_FLATBUFFERS_SOURCES})


file(GLOB DCDR_INTERCONNECT_TEST_FLATBUFFERS_INCLUDES flatbuffers/*.h)

set(INCLUDE_FILES
        ${DCDR_INTERCONNECT_TEST_FLATBUFFERS_INCLUDES})

add_executable(
        ${PROJECT_NAME}
        ${INCLUDE_FILES}
        ${SOURCE_FILES})

add_test(NAME DcdrInterconnectTest COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE test-utils)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-interconnect)