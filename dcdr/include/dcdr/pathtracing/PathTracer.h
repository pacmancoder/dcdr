#pragma once

#include <dcdr/Types.h>
#include <dcdr/renderer/ISampleRenderer.h>
#include <dcdr/scene/IScene.h>

namespace Dcdr::PathTracing
{
    class PathTracer : public Renderer::ISampleRenderer
    {
    public:
        explicit PathTracer(Scene::ScenePtr scene);
        void set_surface_size(Types::Size width, Types::Size height) override;
        Types::Color render_sample(Types::Offset x, Types::Offset y) override;

    private:
        Types::Size surface_width_ = 0;
        Types::Size surface_height_ = 0;

        const Scene::ScenePtr scene_;
    };
}
