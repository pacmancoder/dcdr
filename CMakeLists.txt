cmake_minimum_required(VERSION 3.8)

project(dcdr-suite)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /WX /std:c++latest")
else()
    set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Werror")
endif()

# Output binnaries and shared libraries to the same folder
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Third-party libraries
add_subdirectory(libs)

# Core modules
add_subdirectory(umath)
add_subdirectory(dcdr-common)
add_subdirectory(dcdr-pathtracer)
add_subdirectory(dcdr-worker)

# Tests
add_subdirectory(tests)