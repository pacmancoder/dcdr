project(dcdr-transport)

file(GLOB INCLUDES_TRANSPORT include/dcdr/transport/*.h)
file(GLOB INCLUDES_TRANSPORT_PRIVATE include/dcdr/transport/*.h)

set(INCLUDE_FILES
        ${INCLUDES_TRANSPORT}
        ${INCLUDES_TRANSPORT_PRIVATE})

file(GLOB SOURCES_TRANSPORT src/transport/*.cpp)
file(GLOB SOURCES_TRANSPORT_PRIVATE src/transport/private/*.cpp)

set(SOURCE_FILES
        ${SOURCES_TRANSPORT}
        ${SOURCES_TRANSPORT_PRIVATE})

include_directories(src)
include_directories(include)

add_library(${PROJECT_NAME} STATIC ${INCLUDE_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC dcdr-common)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-logger mongoose)

if (NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)