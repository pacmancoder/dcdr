project(dcdr-worker-cli)


file(GLOB SOURCES src/*.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-worker dcdr-common)