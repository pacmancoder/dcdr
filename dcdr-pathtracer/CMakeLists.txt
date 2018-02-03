project(dcdr-pathtracer)

set(DCDR_PATHTRACER_INCLUDES

        include/dcdr/tracing/Ray.h
        include/dcdr/tracing/IntersectionInfo.h

        include/dcdr/scene/ISceneController.h
        include/dcdr/scene/SceneController.h
        include/dcdr/scene/Camera.h
        include/dcdr/scene/ISceneObject.h
        include/dcdr/scene/IMaterial.h

        include/dcdr/scene/objects/Sphere.h

        include/dcdr/pathtracing/PathTracer.h)

set(DCDR_PATHTRACER_SOURCES

        src/scene/Camera.cpp
        src/scene/SceneController.cpp
        src/scene/objects/Sphere.cpp

        src/pathtracer/PathTracer.cpp)

set(SOURCE_FILES ${DCDR_PATHTRACER_INCLUDES} ${DCDR_PATHTRACER_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

# ToDo: Link dynamic, use generate_export_header
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE umath)
target_link_libraries(${PROJECT_NAME} PRIVATE dcdr-common)

target_include_directories(${PROJECT_NAME} PUBLIC include)