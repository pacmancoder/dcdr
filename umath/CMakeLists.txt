project(umath)

set(INCLUDE_FILES
        include/umath/Vec3.h
        include/umath/Mat4.h
        include/umath/Intersections.h)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)