project(dcdr-worker)

file(GLOB INCLUDES_WORKER include/dcdr/worker/*.h)

set(INCLUDES
        ${INCLUDES_WORKER})

file(GLOB SOURCES_WORKER src/*.cpp)

set(SOURCES
        ${SOURCES_WORKER})

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${INCLUDES} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        dcdr-common
        dcdr-transport
        dcdr-interconnect
        dcdr-pathtracer)

target_link_libraries(${PROJECT_NAME} PUBLIC
        dcdr-logger)

target_include_directories(${PROJECT_NAME} PUBLIC include)