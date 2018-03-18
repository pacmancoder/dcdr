#pragma once

#include <dcdr/Types.h>
#include <dcdr/renderer/Ray.h>
#include <dcdr/renderer/IntersectionInfo.h>

namespace Dcdr::Renderer
{
    class IObjectGeometry
    {
    public:
        virtual bool intersect(
                const Ray& ray,
                const Types::Mat4& objectTransform,
                IntersectionInfo& intersection) const = 0;

        virtual ~IObjectGeometry() = default;
    };
}