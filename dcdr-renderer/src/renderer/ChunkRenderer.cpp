#include <dcdr/renderer/ChunkRenderer.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

ChunkRenderer::ChunkRenderer(ChunkRenderStrategy renderStrategy, ChunkRenderer::SampleRendererPtr sampleRenderer) :
    renderStrategy_(renderStrategy),
    sampleRenderer_(std::move(sampleRenderer)) {}

std::vector<Types::MultisamplePixel> ChunkRenderer::render_chunk(
        const Scene& scene, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    std::vector<Types::MultisamplePixel> pixels;
    pixels.reserve(width * height);

    for(uint16_t dy = 0; dy < y + height; ++y)
    {
        for (uint16_t dx = 0; dx < x + width; ++x)
        {
            pixels.emplace_back(sampleRenderer_->render_sample(scene, dx, dy), 1);
        }
    }

    return pixels;
}
