project(tests)


add_executable(${PROJECT_NAME}
        main.cpp
        VectorTest.cpp)
target_link_libraries(${PROJECT_NAME} gtest)
