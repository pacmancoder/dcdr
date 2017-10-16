project(tests)

include_directories(fixtures)
include_directories(utils)

add_executable(${PROJECT_NAME}
        fixtures/UmathTest.h

        utils/approx.h

        main.cpp

        umath/VectorTest.cpp)

target_link_libraries(${PROJECT_NAME}
        gtest
        umath)
