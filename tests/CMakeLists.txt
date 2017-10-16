project(tests)

include_directories(fixtures)
include_directories(utils)

add_executable(${PROJECT_NAME}
        fixtures/UmathTest.h

        utils/approx.h

        main.cpp

        umath/Vec3Test.cpp
        umath/Mat4Test.cpp)

target_link_libraries(${PROJECT_NAME}
        gtest
        umath)
