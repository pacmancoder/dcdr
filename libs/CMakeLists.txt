project(libs)

add_subdirectory(gtest-1.8.0)
add_subdirectory(mongoose)
add_subdirectory(microtar)
add_subdirectory(flatbuffers-git)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
