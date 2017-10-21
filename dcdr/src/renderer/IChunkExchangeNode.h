#pragma once

#include <DcdrTypes.h>
#include <renderer/Chunk.h>

namespace Dcdr::Renderer {

    enum class ChunkSeizureStatus
    {
        Success,
        AlreadySeizured,
        NotAllowed,
    };

    enum class ChunkReleaseStatus
    {
        Success,
        NotSeizured,
    };

    class IChunkExchangeNode {
    public:
        virtual ChunkSeizureStatus seizure_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) = 0;
        virtual ChunkReleaseStatus release_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) = 0;

        virtual void save_chunk(const Chunk& chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y) = 0;
        virtual Chunk request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) = 0;
    };

}