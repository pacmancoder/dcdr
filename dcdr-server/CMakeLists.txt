project(dcdr-server)


file(GLOB INCLUDES_SERVER include/dcdr/server/*.h)

set(INCLUDE_FILES
		${INCLUDES_SERVER})

file(GLOB SOURCES_SERVER src/server/*.cpp)

set(SOURCE_FILES
		${SOURCES_SERVER}
		src/main.cpp)

include_directories(include)

add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common dcdr-logger dcdr-interconnect dcdr-transport)

if (NOT WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()