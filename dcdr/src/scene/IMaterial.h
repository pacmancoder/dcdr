#pragma once

#include "dcdr/Types.h"

namespace Dcdr::Scene
{
    class IMaterial
    {
    public:
        virtual Dcdr::Types::Vec3 get_albedo(Dcdr::Types::UVCoord uv) = 0;

        virtual Dcdr::Types::Scalar get_roughness() = 0;
        virtual Dcdr::Types::Scalar get_refraction() = 0;

        virtual Dcdr::Types::Scalar get_emitance() = 0;
    };
}