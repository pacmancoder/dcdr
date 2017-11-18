project(dcdr-worker)

set(SOURCE_FILES
        src/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-pathtracer)