#pragma once

#include <dcdr/renderer/SceneObject.h>
#include <dcdr/renderer/IObjectGeometry.h>

namespace Dcdr::Renderer
{
    class SphereGeometry : public IObjectGeometry
    {
    public:
        explicit SphereGeometry(Types::Real radius);

        bool intersect(
                const Ray& ray,
                const Types::Mat4& objectTransform,
                IntersectionInfo& intersection) const override;

    private:
        Types::Real radius_;
    };
}

