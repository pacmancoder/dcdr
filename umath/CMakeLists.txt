project(umath)

set(SOURCE_FILES
        src/Vector.cpp
        include/umath/Vector.h)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)