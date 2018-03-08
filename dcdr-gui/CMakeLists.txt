project(dcdr-gui)

file(GLOB DCDR_GUI_SOURCES src/*.cpp)
file(GLOB DCDR_GUI_INCLUDES include/dcdr/gui/*.h)

include_directories(include)

add_executable(${PROJECT_NAME} ${DCDR_GUI_SOURCES} ${DCDR_GUI_INCLUDES})

set(DCDR_GUI_LINKS dcdr-interconnect dcdr-transport dcdr-logger nana)

if(UNIX)
    set(DCDR_GUI_LINKS ${DCDR_GUI_LINKS} fontconfig pthread)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${DCDR_GUI_LINKS})