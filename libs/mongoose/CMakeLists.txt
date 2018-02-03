project(mongoose)

if(MSVC)
	remove_definitions(/WX)
else()
	remove_definitions(-Werror)
endif()

SET(MONGOOSE_DIR mongoose-git)

SET(MONGOOSE_SOURCES
        ${MONGOOSE_DIR}/mongoose.c)

SET(MONGOOSE_HEADERS
        ${MONGOOSE_DIR}/mongoose.h)

include_directories(${MONGOOSE_DIR})

add_library(${PROJECT_NAME} STATIC
        ${MONGOOSE_SOURCES}
        ${MONGOOSE_HEADERS})

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} PUBLIC ${MONGOOSE_DIR})
