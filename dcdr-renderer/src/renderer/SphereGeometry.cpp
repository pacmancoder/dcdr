#include <dcdr/renderer/SphereGeometry.h>

#include <umath/Intersections.h>
#include <umath/Operations.h>

#include <dcdr/Constants.h>

using namespace Dcdr::Types;
using namespace Dcdr::Renderer;
using namespace UMath;

SphereGeometry::SphereGeometry(Real radius) : radius_(radius) {}

bool SphereGeometry::intersect(
        const Ray& ray,
        const Types::Mat4& objectTransform,
        IntersectionInfo& intersection) const
{
    // At the moment, only spheres are supported; ellipsoids are threaten like spheres.
    Types::Vec3 pos = objectTransform.transform_point(Types::Vec3(0.0f));
    Types::Vec3 radiusVector = objectTransform.transform_direction(Types::Vec3(1.0, 0.0, 0.0));
    Types::Vec3 secondRadiusVector = objectTransform.transform_direction(Types::Vec3(0.0, 1.0, 0.0));

    Real t = Intersections::ray_sphere(ray.pos, ray.dir, pos, radiusVector.len(), Constants::Math::Epsilon);

    if (t < 0) return false;

    intersection.hit = ray.pos + ray.dir * t;
    intersection.normal = (intersection.hit - pos).normalize();

    intersection.uv.v = clamp(radiusVector % intersection.normal, Real(0.0), Real(1.0));
    intersection.uv.u = clamp(secondRadiusVector % intersection.normal, Real(0.0), Real(1.0));

    return true;
}