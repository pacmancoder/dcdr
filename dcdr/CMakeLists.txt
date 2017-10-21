project(dcdr)

set(SOURCE_FILES
        src/DcdrTypes.h

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

        src/tracing/Intersection.h src/renderer/UnbakedPixel.cpp src/renderer/UnbakedPixel.h src/DcdrConstants.h src/DcdrConstants.cpp src/renderer/Chunk.cpp src/renderer/Chunk.h src/renderer/Surface.cpp src/renderer/Surface.h src/renderer/IChunkRenderer.h src/renderer/IChunkExchangeNode.h src/renderer/ChunkExchangeNodeStub.cpp src/renderer/ChunkExchangeNodeStub.h src/renderer/ISurfaceRasterizator.h)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE umath)
target_include_directories(${PROJECT_NAME} PUBLIC include)