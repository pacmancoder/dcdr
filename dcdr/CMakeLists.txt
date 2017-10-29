project(dcdr)

set(DCDR_INCLUDES
        include/dcdr/Types.h
        include/dcdr/Constants.h

        include/dcdr/utils/Iterator.h
        include/dcdr/utils/Rng.h

        include/dcdr/renderer/UnbakedPixel.h
        include/dcdr/renderer/Chunk.h
        include/dcdr/renderer/Surface.h
        include/dcdr/renderer/ISampleRenderer.h
        include/dcdr/renderer/IChunkExchangeNode.h
        include/dcdr/renderer/ISurfaceRasterizer.h

        include/dcdr/tracing/Ray.h
        include/dcdr/tracing/IntersectionInfo.h

        include/dcdr/scene/IScene.h
        include/dcdr/scene/Scene.h
        include/dcdr/scene/Camera.h
        include/dcdr/scene/ISceneObject.h
        include/dcdr/scene/IMaterial.h

        include/dcdr/scene/objects/Sphere.h

        include/dcdr/pathtracing/PathTracer.h)

set(DCDR_SOURCES
        src/Constants.cpp

        src/utils/Rng.cpp

        src/scene/Camera.cpp
        src/scene/Scene.cpp

        src/scene/objects/Sphere.cpp

        src/renderer/UnbakedPixel.cpp
        src/renderer/Chunk.cpp
        src/renderer/Surface.cpp

        src/pathtracer/PathTracer.cpp)

set(SOURCE_FILES ${DCDR_INCLUDES} ${DCDR_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC umath)
target_include_directories(${PROJECT_NAME} PUBLIC include)