#pragma once

#include <scene/ISceneObject.h>
#include <tracing/IntersectionInfo.h>

namespace Dcdr::Tracing
{
    class Intersection
    {
    public:
        Intersection(const Dcdr::Scene::ISceneObject& object, Dcdr::Tracing::IntersectionInfo info) :
                object_(object),
                info_(info) {}

        const Dcdr::Scene::ISceneObject& get_object() { return object_; }

        const Dcdr::Tracing::IntersectionInfo& get_info() { return info_; }

    private:
        const Dcdr::Scene::ISceneObject& object_;
        Dcdr::Tracing::IntersectionInfo info_;
    };
}