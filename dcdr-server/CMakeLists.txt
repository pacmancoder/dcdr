project(dcdr-server)


file(GLOB INCLUDES_SERVER include/dcdr/server/*.h)

set(INCLUDE_FILES
		${INCLUDES_SERVER})

file(GLOB SOURCES_SERVER src/server/*.cpp)

set(SOURCE_FILES
		${SOURCES_SERVER})

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC dcdr-common dcdr-logger dcdr-interconnect dcdr-transport)

if (NOT WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

add_executable(${PROJECT_NAME}-bin src/main.cpp)
target_link_libraries(${PROJECT_NAME}-bin ${PROJECT_NAME})