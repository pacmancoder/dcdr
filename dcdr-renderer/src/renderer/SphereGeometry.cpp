#include <dcdr/renderer/SphereGeometry.h>

#include <dcdr/Constants.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>

using namespace Dcdr::Types;
using namespace Dcdr::Renderer;

SphereGeometry::SphereGeometry(Real radius) : radius_(radius) {}

bool SphereGeometry::intersect(Ray ray, Mat4 objectTransform, IntersectionInfo& intersection) const
{
    // At the moment, only spheres are supported; ellipsoids are threaten like spheres.
    Types::Vec3 pos = objectTransform * Types::Vec4(0.f, 0.f, 0.f, 1.f);
    Types::Vec3 radiusVector = objectTransform * Types::Vec4(1.f, 0.f, 0.f, 0.f);
    Types::Vec3 secondRadiusVector = objectTransform * Types::Vec4(0.f, 1.f, 0.f, 0.f);

    if (!glm::intersectRaySphere(
            ray.pos, ray.dir, pos, glm::length(radiusVector), intersection.hit, intersection.normal))
    {
        return false;
    }

    intersection.uv = glm::clamp(Types::Vec2(
                glm::dot(radiusVector, intersection.normal), glm::dot(secondRadiusVector, intersection.normal)),
            0.f, 1.f);
    return true;
}