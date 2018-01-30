cmake_minimum_required(VERSION 3.8)

project(dcdr-suite)


# TODO: make flags setting look pretty

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /std:c++latest")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    endif(CMAKE_COMPILER_IS_GNUCC)

endif()

# Output binnaries and shared libraries to the same folder
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Third-party libraries
add_subdirectory(libs)

# Core modules
add_subdirectory(umath)
add_subdirectory(dcdr-common)
add_subdirectory(dcdr-logger)
add_subdirectory(dcdr-pathtracer)
add_subdirectory(dcdr-worker)
add_subdirectory(dcdr-interconnect)
add_subdirectory(dcdr-server)
add_subdirectory(dcdr-webui)

# Tests
add_subdirectory(tests)
