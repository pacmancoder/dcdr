project(dcdr-server)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE mongoose)

target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common dcdr-logger dcdr-interconnect dcdr-transport)

if (NOT WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()