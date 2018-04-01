#include <dcdr/renderer/PathTracer.h>
#include <dcdr/Constants.h>
#include <dcdr/utils/Rng.h>

#include <cmath>

using namespace Dcdr::Renderer;
using namespace Dcdr::Types;
using namespace Dcdr::Utils;
using namespace Dcdr;

namespace
{

    Color get_diffuse(const Material& material, UVCoord uv)
    {
        return material.is_texture_assigned(TextureType::Diffuse) ?
               material.get_texture(TextureType::Diffuse).get_color(uv) : Vec3(1.0f);
    }

    Color trace_ray(const Dcdr::Renderer::Scene& scene, Rng sampler, Ray ray, int reflectionsLeft = 15)
    {
        IntersectionInfo intersectionInfo = {};
        auto object = scene.intersect(ray, intersectionInfo);

        Color color(0);

        if (object != nullptr && reflectionsLeft > 0)
        {
            const auto& material = object->get_material();

            if (material.get_params().emittance > Real(0))
            {
                color += get_diffuse(material, intersectionInfo.uv) * material.get_params().emittance;
            }

            if (material.get_params().diffuse > Real(0))
            {

                float a = sampler.generate_real(0, Constants::Math::Pi);
                float b = sampler.generate_real(0, Constants::Math::Pi);

                Vec3 generatedDir(
                        std::cos(a) * std::sin(b),
                        std::sin(a) * std::sin(b),
                        std::cos(b));

                if (glm::dot(generatedDir, intersectionInfo.normal) < 0.f)
                {
                    generatedDir = -generatedDir;
                }

                color += get_diffuse(material, intersectionInfo.uv) *
                        trace_ray(scene, sampler, Ray {intersectionInfo.hit, generatedDir}, reflectionsLeft - 1) *
                         glm::dot(intersectionInfo.normal, generatedDir);

            }

            /*
            if (material.get_params().reflectance > Real(0))
            {
                Vec3 reflectedRay(ray.dir - (glm::dot(intersectionInfo.normal, ray.dir) * intersectionInfo.normal) * 2.f);
                color += trace_ray(
                        scene, sampler, Ray { intersectionInfo.hit, glm::normalize(reflectedRay) }, reflectionsLeft - 1) *
                        material.get_params().reflectance *
                        glm::dot(intersectionInfo.normal, -ray.dir);
            }
            */
        }

        return color;
    }
}

Color Dcdr::Renderer::PathTracer::render_sample(const Dcdr::Renderer::Scene& scene, Real x, Real y)
{
    Camera camera = scene.get_camera();

    Rng sampler;

    Types::Real u = sampler.generate_real(0, 1);
    Types::Real v = sampler.generate_real(0, 1);

    Ray ray = camera.cast_ray(
            Types::Real(x),
            Types::Real(y),
            Types::Size(scene.get_width()),
            Types::Size(scene.get_height()),
            u,
            v,
            sampler);

    return glm::clamp(trace_ray(scene, sampler, ray), Types::Real(0), Types::Real(1));
}
