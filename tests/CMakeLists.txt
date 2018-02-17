project(tests)

include(CTest)
enable_testing()

add_subdirectory(test-utils)
add_subdirectory(umath-test)
add_subdirectory(dcdr-interconnect-test)
add_subdirectory(dcdr-server-test)