project(dcdr-cli)

set(SOURCE_FILES
        src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC dcdr)