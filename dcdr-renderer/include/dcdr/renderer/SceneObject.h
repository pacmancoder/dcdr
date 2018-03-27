#pragma once

#include <string>
#include <memory>

#include <dcdr/Types.h>
#include <dcdr/renderer/Ray.h>
#include <dcdr/renderer/IntersectionInfo.h>
#include <dcdr/renderer/Material.h>
#include <dcdr/renderer/IObjectGeometry.h>

namespace Dcdr::Renderer
{
    class SceneObject
    {
    public:
        using ObjectGeometryPtr = std::shared_ptr<IObjectGeometry>;
        using MaterialPtr = std::shared_ptr<Material>;

    public:
        SceneObject(
                Types::Mat4 transformMatrix,
                const ObjectGeometryPtr& objectGeometry,
                const MaterialPtr& material);

        bool intersect(const Ray& ray, IntersectionInfo& intersection) const;
        const Material& get_material();

    private:
        Types::Mat4 transformMatrix_;
        ObjectGeometryPtr objectGeometry_;
        MaterialPtr material_;
    };
}