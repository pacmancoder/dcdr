#include <dcdr/pathtracing/PathTracer.h>

#include <cmath>

#include <dcdr/scene/objects/Sphere.h>
#include <dcdr/Constants.h>

using namespace Dcdr::Scene;
using namespace Dcdr::Types;
using namespace Dcdr::Utils;

Dcdr::PathTracing::PathTracer::PathTracer(SceneControllerPtr scene) :
        scene_(std::move(scene)) {}

void Dcdr::PathTracing::PathTracer::set_surface_size(Dcdr::Types::Size width, Dcdr::Types::Size height)
{
    surface_width_ = width;
    surface_height_ = height;
}

Dcdr::Types::Color Dcdr::PathTracing::PathTracer::render_sample(Dcdr::Types::Offset x, Dcdr::Types::Offset y)
{
    Camera camera = scene_->get_camera();

    Utils::Rng rng;

    Types::Real u = rng.generate_real(0, 1);
    Types::Real v = rng.generate_real(0, 1);

    Tracing::Ray ray = camera.cast_ray(x, y, surface_width_, surface_height_, u, v, rng);

    for(ConstIteratorPtr<ISceneObject> it = scene_->get_objects_iterator(ray); it->can_advance(); it->advance())
    {
        const ISceneObject& object = it->get();
        Tracing::IntersectionInfo intersection;
        if (object.intersect(ray, intersection))
        {
            Vec3 base_color((ray.dir -  intersection.hit).normalize() % intersection.normal);
            return base_color;
        }
    }
    return Constants::Color::Black;
}
