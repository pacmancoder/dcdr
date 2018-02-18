#include <dcdr/server/core/Surface.h>
#include <atomic>

using namespace Dcdr::Server;

namespace
{
    template<typename T>
    T floor_integer(T a, T b)
    {
        return a / b + ((a % b == 0) ? 0 : 1);
    }

    template<typename T>
    T pow_integer(T a, T b)
    {
        T acc = 1;

        while (b-- > 0)
        {
            acc *= a;
        }

        return acc;
    }

    template<typename T>
    T clamp_integer(T a, T b, T c)
    {
        if (a < b)
        {
            return b;
        }
        if (a > c)
        {
            return c;
        }
        return a;
    }

}

Surface::Surface(uint16_t width, uint16_t height, uint16_t chunkSize) :
    width_(width),
    height_(height),
    chunkSize_(chunkSize),
    widthInChunks_(floor_integer(width, chunkSize)),
    heightInChunks_(floor_integer(height, chunkSize)),
    chunkCounter_(0),
    chunks_()
{
    chunks_.resize(widthInChunks_);
    for (int column = 0; column < widthInChunks_; ++column)
    {
        chunks_[column].resize(heightInChunks_);
        for (int row = 0; row < heightInChunks_; ++row)
        {
            chunks_[column][row] = std::make_shared<Chunk>(ChunkRect{
                    static_cast<uint16_t>(column * chunkSize),
                    static_cast<uint16_t>(row * chunkSize),
                    chunkSize,
                    chunkSize});
        }
    }
}

Surface::Surface(Surface &&rhs) :
    width_(rhs.width_),
    height_(rhs.height_),
    chunkSize_(rhs.chunkSize_),
    widthInChunks_(rhs.widthInChunks_),
    heightInChunks_(rhs.heightInChunks_),
    chunkCounter_(rhs.chunkCounter_),
    chunks_(std::move(rhs.chunks_)) {}

ChunkRect Surface::next_chunk_to_render()
{
    std::lock_guard<std::mutex> guard(chunksMutex_);

    auto bounds = std::atomic_load(
            &chunks_[chunkCounter_ % widthInChunks_][(chunkCounter_ / widthInChunks_) % heightInChunks_])->get_bounds();
    ++chunkCounter_;

    return bounds;
}

SurfaceBuffer Surface::get_surface_buffer(
        SurfaceBufferFormat format, uint8_t mipmapLevel, MipmappingTechnique /*mipmappingTechnique*/) const
{
    // Temporary implementataion. TODO: change this to universal implementation
    auto scaleDownFactor = pow_integer(uint8_t(2), mipmapLevel);

    auto resultWidth = width_ / scaleDownFactor;
    auto resultHeight = height_ / scaleDownFactor;

    SurfaceBuffer buffer {
            format,
            static_cast<uint16_t>(resultWidth),
            static_cast<uint16_t>(resultHeight),
            std::vector<uint8_t>(static_cast<size_t>(resultWidth * resultHeight * 3))};


    for (int row = 0; row < heightInChunks_; ++row)
    {
        for (int column = 0; column < widthInChunks_; ++column)
        {
            auto startPixelOffset = (row * chunkSize_ * width_ / scaleDownFactor + column * chunkSize_) * 3 / scaleDownFactor;
            auto rowSize = width_ * 3 / scaleDownFactor;

            auto chunk = std::atomic_load(&chunks_[column][row]);
            auto chunkBounds = chunk->get_bounds();
            for (size_t y = 0; y < chunkBounds.h; y += scaleDownFactor)
            {
                for (size_t x = 0; x < chunkBounds.w; x += scaleDownFactor)
                {
                    auto pixelOffset = startPixelOffset + (rowSize * y + x * 3) / scaleDownFactor;
                    auto color = chunk->get_pixels()[y * chunkBounds.w + x].color;
                    buffer.data[pixelOffset + 0] =
                            static_cast<uint8_t>(clamp_integer<size_t>(static_cast<size_t>(color.r * 255), 0, 255));
                    buffer.data[pixelOffset + 1] =
                            static_cast<uint8_t>(clamp_integer<size_t>(static_cast<size_t>(color.g * 255), 0, 255));
                    buffer.data[pixelOffset + 2] =
                            static_cast<uint8_t>(clamp_integer<size_t>(static_cast<size_t>(color.b * 255), 0, 255));
                }
            }
        }
    }

    return buffer;
}

void Surface::commit_chunk(const Chunk& chunk)
{
    auto* chunkAddr =
            &chunks_[chunk.get_bounds().x / chunkSize_][chunk.get_bounds().y / chunkSize_];

    auto newChunk = std::make_shared<Chunk>(*std::atomic_load(chunkAddr));
    newChunk->accumulate(chunk);
    std::atomic_store(chunkAddr, newChunk);
}

const Chunk Surface::read_chunk(size_t chunkX, size_t chunkY) const
{
    auto chunkPtr = std::atomic_load(&chunks_[chunkX][chunkY]);
    return Chunk(*chunkPtr);
}
