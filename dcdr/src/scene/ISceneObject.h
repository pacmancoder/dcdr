#pragma once

#include <DcdrTypes.h>
#include <tracing/Ray.h>
#include <tracing/IntersectionInfo.h>

namespace Dcdr::Scene
{
    class ISceneObject
    {
    public:
        virtual bool intersect(Dcdr::Tracing::Ray& ray, Dcdr::Tracing::IntersectionInfo& intersection) = 0;
    };
}