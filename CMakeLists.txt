cmake_minimum_required(VERSION 3.8)

project(dcdr-suite)

# Common flags
if(MSVC)
	add_definitions(/W4 /WX /std:c++latest)
else()
	add_definitions(-Wall -Wextra -Werror)
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# Debug flags
    if(CMAKE_COMPILER_IS_GNUCC)
		add_definitions(-O0)
    endif(CMAKE_COMPILER_IS_GNUCC)
else()
# Release flags
endif()

# Output binaries and shared libraries to the same folder

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)


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
