project(libs)

# Be acknowledged about issues in libraries, but not threat them as critical
if (MSVC)
	option(gtest_force_shared_crt "" ON)
    string(REGEX REPLACE "/WX" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    string(REGEX REPLACE "-Werror" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(gtest-git)
add_subdirectory(mongoose)
add_subdirectory(microtar)

option(FLATBUFFERS_BUILD_TESTS "" OFF)
option(FLATBUFFERS_INSTALL "" OFF)
option(FLATBUFFERS_BUILD_FLATHASH "" OFF)

add_subdirectory(flatbuffers-git)
add_subdirectory(lodepng)

option(NANA_CMAKE_VERBOSE_PREPROCESSOR "" OFF)

if (MSVC)
    option(MSVC_USE_STATIC_RUNTIME "" OFF)
endif()

add_subdirectory(nana-git)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
