#include <dcdr/renderer/Scene.h>

#include <dcdr/renderer/RendererExceptions.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

Scene::Scene(uint16_t width, uint16_t height) :
    width_(width),
    height_(height),
    camera_(nullptr),
    objects_() {}

void Scene::add_object(const Scene::SceneObjectPtr& object)
{
    objects_.push_front(object);
}

void Scene::set_camera(const Scene::CameraPtr& camera)
{
    camera_ = camera;
}

uint16_t Scene::get_width() const
{
    return width_;
}

uint16_t Scene::get_height() const
{
    return height_;
}

Camera& Scene::get_camera() const
{
    if (camera_ == nullptr)
    {
        throw SceneException("Camera is not initialized");
    }

    return *camera_;
}

Scene::SceneObjectPtr Scene::intersect(const Ray& ray, IntersectionInfo& info) const
{
    Scene::SceneObjectPtr hitObject = nullptr;
    IntersectionInfo lastHit;

    for (const auto& object : objects_)
    {
        if (object->intersect(ray, lastHit))
        {
            if (hitObject == nullptr ||
                (info.hit - camera_->get_pos()).len() > (lastHit.hit - camera_->get_pos()).len())
            {
                info = lastHit;
                hitObject = object;
            }
        }
    }

    return hitObject;
}
