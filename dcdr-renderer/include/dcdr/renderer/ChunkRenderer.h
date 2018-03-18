#pragma once

#include <dcdr/Types.h>
#include <dcdr/renderer/Scene.h>
#include <dcdr/renderer/ISampleRenderer.h>

#include <vector>
#include <memory>

namespace Dcdr::Renderer
{
    enum class ChunkRenderStrategy
    {
        Normal,
        Adaptive
    };

    class ChunkRenderer
    {
    public:
        using SampleRendererPtr = std::unique_ptr<ISampleRenderer>;

    public:
        ChunkRenderer(ChunkRenderStrategy renderStrategy, SampleRendererPtr sampleRenderer);

         std::vector<Types::MultisamplePixel> render_chunk(
                 const Scene& scene, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    private:
        ChunkRenderStrategy renderStrategy_;
        SampleRendererPtr sampleRenderer_;
    };
}