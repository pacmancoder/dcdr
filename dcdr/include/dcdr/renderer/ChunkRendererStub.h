#pragma once

#include <dcdr/renderer/IChunkRenderer.h>

namespace Dcdr::Renderer
{

    class ChunkRendererStub : public IChunkRenderer
    {
    public:
        Types::Color render_sample(Types::Offset x, Types:: Offset y) override;
    };

}