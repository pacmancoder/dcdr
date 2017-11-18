#pragma once

#include <string>
#include <memory>

#include <dcdr/Types.h>
#include <dcdr/tracing/Ray.h>
#include <dcdr/tracing/IntersectionInfo.h>

namespace Dcdr::Scene
{
    class ISceneObject
    {
    public:
        virtual bool intersect(const Tracing::Ray& ray, Tracing::IntersectionInfo& intersection) const = 0;
        virtual Types::Offset get_material_map_index() const = 0;

        virtual ~ISceneObject() = default;
    };

    typedef std::shared_ptr<ISceneObject> SceneObjectPtr;
    typedef std::unique_ptr<ISceneObject> SceneObjectUniquePtr;
}