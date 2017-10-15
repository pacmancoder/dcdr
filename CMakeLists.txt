cmake_minimum_required(VERSION 3.8)

project(dcdr-suite)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libs)

add_subdirectory(umath)
add_subdirectory(dcdr)
add_subdirectory(dcdr-cli)

add_subdirectory(tests)