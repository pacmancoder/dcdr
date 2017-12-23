project(dcdr-logger)

set(DCDR_LOGGER_INCLUDES
        include/dcdr/logging/Logger.h
        include/dcdr/logging/ILogWriter.h
        include/dcdr/logging/FileLogWriter.h
        include/dcdr/logging/StdoutLogWriter.h)

set(DCDR_LOGGER_SOURCES
        src/logging/Logger.cpp
        src/logging/FileLogWriter.cpp
        src/logging/StdoutLogWriter.cpp)

set(SOURCE_FILES ${DCDR_LOGGER_INCLUDES} ${DCDR_LOGGER_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)