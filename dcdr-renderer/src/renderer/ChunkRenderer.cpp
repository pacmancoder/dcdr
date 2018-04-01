#include <dcdr/renderer/ChunkRenderer.h>

#include <dcdr/utils/StopWatch.h>
#include <dcdr/logging/Logger.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;
using namespace Dcdr::Logging;

namespace
{
    const char* LOG_PREFIX = "[Renderer] ";
}

ChunkRenderer::ChunkRenderer(ChunkRenderStrategy renderStrategy, ChunkRenderer::SampleRendererPtr sampleRenderer) :
    renderStrategy_(renderStrategy),
    sampleRenderer_(std::move(sampleRenderer)) {}

std::vector<Types::MultisamplePixel> ChunkRenderer::render_chunk(
        const Scene& scene, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

    Utils::StopWatch stopWatch;

    std::vector<Types::MultisamplePixel> pixels;
    pixels.reserve(width * height);

    const size_t ITERATIONS = 8;
    for(uint16_t dy = y; dy < y + height; ++dy)
    {
        for (uint16_t dx = x; dx < x + width; ++dx)
        {
            Types::Color pixel(0);

            for (size_t i = 0; i < ITERATIONS; ++i)
            {
                pixel += sampleRenderer_->render_sample(scene, dx, dy);
            }

            pixels.emplace_back(pixel, ITERATIONS);
        }
    }

    log_trace(LOG_PREFIX, "Chunk rendered in ", stopWatch.duration().count());

    return pixels;
}
