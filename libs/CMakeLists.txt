project(libs)

if (MSVC)
	option(gtest_force_shared_crt "" ON)
    remove_definitions(/WX)
else()
    remove_definitions(-Werror)
endif()
add_subdirectory(gtest-git)
add_subdirectory(mongoose)
add_subdirectory(microtar)
add_subdirectory(flatbuffers-git)
add_subdirectory(lodepng)

set(NANA_CMAKE_VERBOSE_PREPROCESSOR OFF)
add_subdirectory(nana-git)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
