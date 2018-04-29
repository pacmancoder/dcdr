project(dcdr-worker)

file(GLOB INCLUDES_WORKER include/dcdr/worker/*.h)
file(GLOB INCLUDES_DATABASE include/dcdr/database/*.h)

set(INCLUDES
        ${INCLUDES_WORKER}
        ${INCLUDES_DATABASE})

file(GLOB SOURCES_WORKER src/worker/*.cpp)
file(GLOB SOURCES_DATABASE src/database/*.cpp)

set(SOURCES
        ${SOURCES_WORKER}
        ${SOURCES_DATABASE})

include_directories(include)
include_directories(${sqlite3_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${INCLUDES} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
        dcdr-common
        dcdr-transport
        dcdr-interconnect
        mcrt
        microtar
        sqlite3
        dl
        pthread)

target_link_libraries(${PROJECT_NAME} PUBLIC
        dcdr-logger)

target_include_directories(${PROJECT_NAME} PUBLIC include)