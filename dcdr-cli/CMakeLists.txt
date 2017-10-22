project(dcdr-cli)

find_package(SDL2 REQUIRED)

set(SOURCE_FILES
        src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PUBLIC dcdr)