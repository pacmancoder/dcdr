#pragma once

#include <dcdr/Types.h>
#include <vector>

namespace Dcdr::Server
{
    struct ChunkRect
    {
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
    };

    struct ChunkPixel
    {
        Types::Vec3 color;
        uint32_t samples;
    };

    extern bool operator==(const ChunkPixel& a, const ChunkPixel& b);

    class Chunk
    {
    public:
        Chunk(ChunkRect bounds);
        Chunk(ChunkRect bounds, std::vector<ChunkPixel> pixels);
        Chunk(const Chunk&);

        void accumulate(const Chunk& chunk);

        const ChunkRect& get_bounds() const;
        uint32_t get_max_samples() const;
        uint32_t get_min_samples() const;

        const std::vector<ChunkPixel>& get_pixels() const;

    private:
        ChunkRect bounds_;
        std::vector<ChunkPixel> pixels_;
        uint32_t minSamples_;
        uint32_t maxSamples_;
    };
}