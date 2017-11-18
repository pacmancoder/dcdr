#include <dcdr/scene/objects/Sphere.h>

#include <umath/Intersections.h>

#include <dcdr/Constants.h>

using namespace Dcdr::Types;
using namespace Dcdr::Tracing;
using namespace UMath;

Dcdr::Scene::Sphere::Sphere(Vec3 center, Real radius, Offset material_map_index) :
    center_(center), radius_(radius), material_map_index_(material_map_index) {}

bool Dcdr::Scene::Sphere::intersect(const Ray& ray, IntersectionInfo& intersection) const
{
    Real t = Intersections::ray_sphere(ray.pos, ray.dir, center_, radius_, Constants::Math::Epsilon);
    if (t < 0) return false;

    intersection.hit = ray.pos + ray.dir * t;
    intersection.normal = (intersection.hit - center_).normalize();

    intersection.uv.v = ((Types::Vec3(1).x_axis() % intersection.normal) + 1) / Real(2.0);
    intersection.uv.u = ((Types::Vec3(1).y_axis() % intersection.normal) + 1) / Real(2.0);

    return true;
}

Dcdr::Types::Offset Dcdr::Scene::Sphere::get_material_map_index() const
{
    return material_map_index_;
}