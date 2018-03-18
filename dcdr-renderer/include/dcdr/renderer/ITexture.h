#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class ITexture
    {
    public:
        virtual Types::Vec3 get_color(Types::UVCoord uv) const = 0;

        virtual ~ITexture() = default;
    };
}