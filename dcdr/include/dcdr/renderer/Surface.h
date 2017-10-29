#pragma once

#include <dcdr/renderer/Chunk.h>
#include <dcdr/renderer/IChunkExchangeNode.h>
#include <dcdr/renderer/ISampleRenderer.h>
#include <dcdr/renderer/ISurfaceRasterizer.h>

#include <deque>
#include <mutex>
#include <memory>

namespace Dcdr::Renderer
{
    class Surface : IChunkExchangeNode
    {
    public:
        Surface(Types::Size width, Types::Size height, Types::Size chunk_size,
                IChunkExchangeNode& linkedChunkExchangeNode);

        ChunkSeizureStatus seizure_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;

        ChunkReleaseStatus release_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;

        void save_chunk(const Chunk& chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;

        Chunk request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;

        void render_single_chunk(ISampleRenderer& renderer);

        void set_rasterizer(std::shared_ptr<ISurfaceRasterizer> rasterizer);

        Surface(Chunk& rhs) = delete;

        Chunk& operator=(const Chunk& rhs) = delete;

    private:
        std::deque<Chunk> chunksPool_;

        Types::Size width_;
        Types::Size height_;

        Types::Size chunk_size_;
        Types::Offset current_chunk_;

        std::shared_ptr<ISurfaceRasterizer> rasterizer_;
        IChunkExchangeNode& linkedChunkExchangeNode_;
    };

}