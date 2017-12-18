project(libs)

add_subdirectory(gtest-1.8.0)
add_subdirectory(mongoose-git)
add_subdirectory(microtar-git)
add_subdirectory(flatbuffers-git)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
