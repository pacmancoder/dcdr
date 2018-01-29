project(lodepng)

set(LODEPNG_DIR lodepng-git)

set(LODEPNG_INCLUDES
	${LODEPNG_DIR}/lodepng.h)

set(LODEPNG_SOURCES
	${LODEPNG_DIR}/lodepng.cpp)

# This is not needed for DCDR operation. All images will 
# be loaded into memory before compression/decompresssion
add_definitions(-DLODEPNG_NO_COMPILE_DISK)

add_library(${PROJECT_NAME} STATIC ${LODEPNG_INCLUDES} ${LODEPNG_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} PUBLIC ${LODEPNG_DIR})
