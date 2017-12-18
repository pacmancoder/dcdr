project(dcdr-interconnect-test)

add_executable(
        ${PROJECT_NAME}

        FlatBuffersExchangeTest.cpp
        main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE test-utils)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-interconnect)