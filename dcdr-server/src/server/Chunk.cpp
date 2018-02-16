#include <dcdr/server/Chunk.h>

#include <dcdr/server/ServerExceptions.h>

using namespace Dcdr::Server;

Chunk::Chunk(ChunkRect bounds) :
    bounds_(bounds),
    pixels_(bounds.w * bounds.h),
    minSamples_(0),
    maxSamples_(0) {}

Chunk::Chunk(ChunkRect bounds, std::vector<ChunkPixel> pixels) :
    Chunk(bounds)
{
    if (pixels.size() != pixels_.size())
    {
        throw ChunkException("Chunk pixel buffers size are not equal");
    }
    pixels_ = std::move(pixels_);

    minSamples_ = pixels[0].samples;
    maxSamples_ = pixels[0].samples;

    for(const auto& pixel : pixels_)
    {
        if (pixel.samples > maxSamples_)
        {
            maxSamples_ = pixel.samples;
        }

        if (pixel.samples < minSamples_)
        {
            minSamples_ = pixel.samples;
        }
    }
}

void Chunk::accumulate(Chunk& chunk)
{
    if (chunk.pixels_.size() != pixels_.size())
    {
        throw ChunkException("Chunk pixel buffers size are not equal");
    }

    for (size_t i = 0; i < pixels_.size(); ++i)
    {
        pixels_[i].samples += chunk.pixels_[i].samples;
        pixels_[i].color +=
                (chunk.pixels_[i].color - pixels_[i].color) * chunk.pixels_[i].samples // weight of new samples
                / static_cast<Types::Real>(pixels_[i].samples); // weight in overall color

    }
}

const ChunkRect& Chunk::get_bounds() const
{
    return bounds_;
}

uint32_t Chunk::get_max_samples() const
{
    return maxSamples_;
}

uint32_t Chunk::get_min_samples() const
{
    return minSamples_;
}

const std::vector<ChunkPixel>& Chunk::get_pixels() const
{
    return pixels_;
}
