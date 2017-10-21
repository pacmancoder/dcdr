#include "Chunk.h"

#include <algorithm>


using namespace Dcdr;
using namespace Dcdr::Renderer;

Chunk::Chunk(Types::Offset x, Types::Offset y, Types::Size width, Types::Size height) :
    global_x_(x),
    global_y_(y),
    width_(width),
    height_(height),
    pixels_(height * width) {}

Chunk::Chunk(const Chunk &rhs) :
    global_x_(rhs.global_x_),
    global_y_(rhs.global_y_),
    width_(rhs.width_),
    height_(rhs.height_),
    pixels_(rhs.pixels_) {}

void Chunk::add_sample(Types::Offset x, Types::Offset y, Types::Vec3 sample)
{
    pixels_[y * width_ + x].add_sample(sample);
}


void Chunk::render_chunk(IChunkRenderer& renderer)
{
    for (Types::Offset y = 0; y < height_; ++y)
    {
        for (Types::Offset x = 0; x < height_; ++x)
        {
            add_sample(x, y, renderer.render_sample(x + global_x_, y + global_y_));
        }
    }
}