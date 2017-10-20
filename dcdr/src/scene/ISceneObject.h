#pragma once

#include <DcdrTypes.h>
#include <tracing/Ray.h>
#include <tracing/Intersection.h>

namespace Dcdr::Scene
{
    class ISceneObject
    {
    public:
        virtual bool intersect(Dcdr::Tracing::Ray& ray, Dcdr::Tracing::Intersection& intersection) = 0;
    };
}