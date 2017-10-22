#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class IChunkRenderer
    {
    public:
        virtual Types::Color render_sample(Types::Offset x, Types::Offset y) = 0;
    };

}
