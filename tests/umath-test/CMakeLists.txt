project(umath-test)

add_executable(
        ${PROJECT_NAME}
        UmathTest.h

        main.cpp

        Vec3Test.cpp
        Mat4Test.cpp)
add_test(NAME UMathTest COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE test-utils)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE umath)
