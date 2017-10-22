project(dcdr)

set(SOURCE_FILES
        include/dcdr/Types.h

        src/Tracer.cpp
        include/dcdr/Tracer.h

        src/scene/Camera.cpp
        src/scene/Camera.h
        src/scene/ISceneObject.h
        src/scene/IMaterial.h

        src/scene/objects/Sphere.cpp
        src/scene/objects/Sphere.h

        src/tracing/IntersectionInfo.h
        src/tracing/Ray.h

        src/tracing/Intersection.h src/renderer/UnbakedPixel.cpp include/dcdr/renderer/UnbakedPixel.h include/dcdr/Constants.h src/Constants.cpp src/renderer/Chunk.cpp include/dcdr/renderer/Chunk.h src/renderer/Surface.cpp include/dcdr/renderer/Surface.h include/dcdr/renderer/IChunkRenderer.h include/dcdr/renderer/IChunkExchangeNode.h src/renderer/ChunkExchangeNodeStub.cpp include/dcdr/renderer/ChunkExchangeNodeStub.h include/dcdr/renderer/ISurfaceRasterizer.h src/renderer/ChunkRendererStub.cpp include/dcdr/renderer/ChunkRendererStub.h)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC umath)
target_include_directories(${PROJECT_NAME} PUBLIC include)