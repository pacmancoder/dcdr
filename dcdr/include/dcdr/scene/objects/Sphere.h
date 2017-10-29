#pragma once

#include <dcdr/scene/ISceneObject.h>

namespace Dcdr::Scene
{
    class Sphere : public ISceneObject
    {
    public:
        Sphere(Types::Vec3 center, Types::Real radius, Types::Offset material_map_index);

        bool intersect(const Tracing::Ray& ray, Tracing::IntersectionInfo& intersection) const override;

        Types::Offset get_material_map_index() const override;

    private:
        Types::Vec3 center_;
        Types::Real radius_;
        Types::Offset material_map_index_;
    };
}

