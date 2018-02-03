project(libs)

if (MSVC)
	option(gtest_force_shared_crt "" ON)
endif()
add_subdirectory(gtest-git)
add_subdirectory(mongoose)
add_subdirectory(microtar)
add_subdirectory(flatbuffers-git)
add_subdirectory(lodepng)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
