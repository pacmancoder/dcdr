#pragma once

#include <dcdr/Types.h>
#include <dcdr/renderer/Scene.h>

namespace Dcdr::Renderer
{
    class ISampleRenderer
    {
    public:
        virtual Types::Color render_sample(const Scene& scene, Types::Real x, Types::Real y) = 0;

        virtual ~ISampleRenderer() = default;
    };

}
