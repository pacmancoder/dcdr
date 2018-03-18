#pragma once

#include <dcdr/Types.h>
#include <dcdr/renderer/ISampleRenderer.h>

namespace Dcdr::Renderer
{
    class PathTracer : public Renderer::ISampleRenderer
    {
    public:
        Types::Color render_sample(const Scene& scene, Types::Real x, Types::Real y) override;

    };
}
