#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class ISampleRenderer
    {
    public:
        virtual void set_surface_size(Types::Size width, Types::Size height) = 0;

        virtual Types::Color render_sample(Types::Offset x, Types::Offset y) = 0;
    };

}
