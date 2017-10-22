#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Scene
{
    class IMaterial
    {
    public:
        virtual Types::Vec3 get_albedo(Types::UVCoord uv) = 0;

        virtual Types::Real get_roughness() = 0;

        virtual Types::Real get_refraction() = 0;

        virtual Types::Real get_emitance() = 0;
    };
}