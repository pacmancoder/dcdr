project(dcdr)

set(SOURCE_FILES
        src/Tracer.cpp
        include/dcdr/Tracer.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE umath)
target_include_directories(${PROJECT_NAME} PUBLIC include)