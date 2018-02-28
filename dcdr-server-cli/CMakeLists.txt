project(dcdr-server-cli)

# Actual dcdr-server core. Module has been divided into lib/bin to allow bore flexible testing
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} dcdr-server)