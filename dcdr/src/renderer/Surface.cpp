#include <dcdr/renderer/Surface.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

Surface::Surface(Types::Size width, Types::Size height, Types::Size chunk_size,
                 IChunkExchangeNode& linkedChunkExchangeNode) :
        chunksPool_(),
        width_(width),
        height_(height),
        chunk_size_(chunk_size),
        current_chunk_(0),
        rasterizer_(nullptr),
        linkedChunkExchangeNode_(linkedChunkExchangeNode)
{
    for (auto y = 0; y < height / chunk_size; ++y)
        for (auto x = 0; x < width / chunk_size; ++x)
            chunksPool_.emplace_back(Chunk(x * chunk_size, y * chunk_size, chunk_size, chunk_size));
}

ChunkSeizureStatus Surface::seizure_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return ChunkSeizureStatus::Success;
}

ChunkReleaseStatus Surface::release_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return ChunkReleaseStatus::Success;
}


void Surface::save_chunk(const Chunk& chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    chunksPool_[y * (width_ / chunk_size_) + x] = chunk;
}

Chunk Surface::request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return chunksPool_[y * (width_ / chunk_size_) + x];
}

void Surface::render_single_chunk(ISampleRenderer& renderer)
{
    renderer.set_surface_size(width_, height_);

    Types::Offset current_chunk_x = current_chunk_ % (width_ / chunk_size_);
    Types::Offset current_chunk_y = current_chunk_ / (width_ / chunk_size_);

    linkedChunkExchangeNode_.seizure_chunk(current_chunk_x, current_chunk_y);

    chunksPool_[current_chunk_].render_chunk(renderer);

    if (rasterizer_ != nullptr)
    {
        for (Types::Offset i = 0; i < chunk_size_; ++i)
            for (Types::Offset j = 0; j < chunk_size_; ++j)
                rasterizer_->draw_pixel(
                        chunksPool_[current_chunk_].get_pixel(j, i),
                        chunksPool_[current_chunk_].get_chunk_pos_x() + j,
                        chunksPool_[current_chunk_].get_chunk_pos_y() + i);
    }

    linkedChunkExchangeNode_.release_chunk(current_chunk_x, current_chunk_y);
    linkedChunkExchangeNode_.save_chunk(chunksPool_[current_chunk_], current_chunk_x, current_chunk_y);

    current_chunk_ = Types::Offset((current_chunk_ + 1) % chunksPool_.size());
}

void Surface::set_rasterizer(std::shared_ptr<ISurfaceRasterizer> rasterizer)
{
    rasterizer_ = rasterizer;
}
