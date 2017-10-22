#pragma once

#include <dcdr/Types.h>
#include <tracing/Ray.h>
#include <tracing/IntersectionInfo.h>

namespace Dcdr::Scene
{
    class ISceneObject
    {
    public:
        virtual bool intersect(Tracing::Ray& ray, Tracing::IntersectionInfo& intersection) = 0;
    };
}