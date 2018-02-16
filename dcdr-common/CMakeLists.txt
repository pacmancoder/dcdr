project(dcdr-common)

set(DCDR_COMMON_INCLUDES
        include/dcdr/Types.h
        include/dcdr/Constants.h

        include/dcdr/utils/Iterator.h
        include/dcdr/utils/Rng.h
        include/dcdr/utils/Timer.h

        include/dcdr/renderer/UnbakedPixel.h
        include/dcdr/renderer/Chunk.h
        include/dcdr/renderer/ISampleRenderer.h
        include/dcdr/renderer/ISPPDistribution.h include/dcdr/Exception.h)

set(DCDR_COMMON_SOURCES
        src/Constants.cpp

        src/utils/Rng.cpp

        src/renderer/UnbakedPixel.cpp
        src/renderer/Chunk.cpp)

set(SOURCE_FILES ${DCDR_COMMON_INCLUDES} ${DCDR_COMMON_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME} PUBLIC umath)
target_include_directories(${PROJECT_NAME} PUBLIC include)