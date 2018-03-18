cmake_minimum_required(VERSION 3.8)

project(dcdr-suite)

set(CMAKE_CXX_STANDARD 17)

# Common flags
if(MSVC)
	# Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")

else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# Debug flags
    if(CMAKE_COMPILER_IS_GNUCC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
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
add_subdirectory(dcdr-renderer)
add_subdirectory(dcdr-worker)
add_subdirectory(dcdr-worker-cli)
add_subdirectory(dcdr-transport)
add_subdirectory(dcdr-interconnect)
add_subdirectory(dcdr-server)
add_subdirectory(dcdr-server-cli)
add_subdirectory(dcdr-gui)

# Tests
add_subdirectory(tests)
