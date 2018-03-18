#include <dcdr/renderer/PathTracer.h>
#include <dcdr/Constants.h>
#include <dcdr/utils/Rng.h>

#include <cmath>

using namespace Dcdr::Renderer;
using namespace Dcdr::Types;
using namespace Dcdr::Utils;

Color Dcdr::Renderer::PathTracer::render_sample(const Dcdr::Renderer::Scene& scene, Real x, Real y)
{
    Camera camera = scene.get_camera();

    Rng rng;

    Types::Real u = rng.generate_real(0, 1);
    Types::Real v = rng.generate_real(0, 1);

    Ray ray = camera.cast_ray(
            Types::Real(x), Types::Real(y), Types::Size(scene.get_width()), Types::Size(scene.get_height()), u, v, rng);

    IntersectionInfo intersectionInfo = {};
    auto object = scene.intersect(ray, intersectionInfo);

    if (object != nullptr)
    {
        auto diffuseColor = object->get_material().get_texture(TextureType::Diffuse).get_color(intersectionInfo.uv);
        auto diffuseIntensity = (intersectionInfo.normal % ray.dir) * object->get_material().get_params().diffuse;

        return diffuseColor * diffuseIntensity;
    }

    return Constants::Color::Black;
}
