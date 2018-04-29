project(dcdr-renderer)

file(GLOB SOURCE_FILES src/renderer/*.cpp)
file(GLOB INCLUDE_FILES include/dcdr/renderer/*.h)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC
        dcdr-common )

target_link_libraries(${PROJECT_NAME} PRIVATE
        dcdr-logger
        microtar
        mcrt-dcdr)

if (NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()