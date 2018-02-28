project(dcdr-server)


file(GLOB INCLUDES_SERVER include/dcdr/server/*.h)
file(GLOB INCLUDES_SERVER_CORE include/dcdr/server/core/*.h)
file(GLOB INCLUDES_SERVER_LOADERS include/dcdr/server/loaders/*.h)
file(GLOB INCLUDES_SERVER_SERVICE_COMMANDER include/dcdr/server/service-commander/*.h)
file(GLOB INCLUDES_SERVER_SERVICE_WORKER include/dcdr/server/service-worker/*.h)

set(INCLUDE_FILES
		${INCLUDES_SERVER}
		${INCLUDES_SERVER_CORE}
		${INCLUDES_SERVER_LOADERS}
		${INCLUDES_SERVER_SERVICE_COMMANDER}
		${INCLUDES_SERVER_SERVICE_WORKER})

file(GLOB SOURCES_SERVER src/server/*.cpp)
file(GLOB SOURCES_SERVER_CORE src/server/core/*.cpp)
file(GLOB SOURCES_SERVER_LOADERS src/server/loaders/*.cpp)
file(GLOB SOURCES_SERVER_SERVICE_COMMANDER src/server/service-commander/*.cpp)
file(GLOB SOURCES_SERVER_SERVICE_WORKER src/server/service-worker/*.cpp)

set(SOURCE_FILES
		${SOURCES_SERVER}
		${SOURCES_SERVER_CORE}
		${SOURCES_SERVER_LOADERS}
		${SOURCES_SERVER_SERVICE_COMMANDER}
		${SOURCES_SERVER_SERVICE_WORKER})

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC dcdr-common dcdr-logger dcdr-interconnect dcdr-transport)

if (NOT WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()