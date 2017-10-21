#include "Surface.h"

using namespace Dcdr;
using namespace Dcdr::Renderer;

Surface::Surface(Types::Size width, Types::Size height, Types::Size chunk_size,
                 IChunkExchangeNode& linkedChunkExchangeNode) :
    width_(width),
    height_(height),
    chunk_size_(chunk_size),
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


void Surface::save_chunk(const Chunk &chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    chunksPool_[y * (width_ / chunk_size_) + x] = chunk;
}

Chunk Surface::request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return chunksPool_[y * (width_ / chunk_size_) + x];
}

void Surface::render_single_chunk(IChunkRenderer& renderer)
{
    linkedChunkExchangeNode_.seizure_chunk(0, 0);

    chunksPool_[0].render_chunk(renderer);

    linkedChunkExchangeNode_.release_chunk(0, 0);
    linkedChunkExchangeNode_.save_chunk(chunksPool_[0], 0, 0);
}

void Surface::set_rasterizer(std::shared_ptr<ISurfaceRasterizator> rasterizer)
{
    rasterizer_ = rasterizer;
}
