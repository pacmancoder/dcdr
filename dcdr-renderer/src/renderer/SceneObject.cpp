#include <dcdr/renderer/SceneObject.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

SceneObject::SceneObject(
        Types::Mat4 transformMatrix,
        const SceneObject::ObjectGeometryPtr& objectGeometry,
        const SceneObject::MaterialPtr& material) :
    transformMatrix_(transformMatrix),
    objectGeometry_(objectGeometry),
    material_(material) {}

bool SceneObject::intersect(const Ray& ray, IntersectionInfo& intersection) const
{
    return objectGeometry_->intersect(ray, transformMatrix_, intersection);
}

IMaterial& SceneObject::get_material()
{
    return *material_;
}
