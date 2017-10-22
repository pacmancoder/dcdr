#pragma once

#include <dcdr/renderer/IChunkExchangeNode.h>
#include <dcdr/renderer/Chunk.h>

namespace Dcdr::Renderer
{
    class ChunkExchangeNodeStub : public IChunkExchangeNode
    {
    public:
        ChunkSeizureStatus seizure_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;
        ChunkReleaseStatus release_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;

        void save_chunk(const Chunk& chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;
        Chunk request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override;
    private:

    };
}

