#include <dcdr/renderer/ChunkExchangeNodeStub.h>


using namespace Dcdr;
using namespace Dcdr::Renderer;

ChunkSeizureStatus ChunkExchangeNodeStub::seizure_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return ChunkSeizureStatus::Success;
}

ChunkReleaseStatus ChunkExchangeNodeStub::release_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return ChunkReleaseStatus::Success;
}

void ChunkExchangeNodeStub::save_chunk(const Chunk &chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    // skip request
}

Chunk ChunkExchangeNodeStub::request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    return Chunk(x, y, 16, 16);
}
