#pragma once

#include <memory>
#include <forward_list>

#include <dcdr/renderer/Camera.h>
#include <dcdr/renderer/SceneObject.h>

namespace Dcdr::Renderer
{
    class Scene
    {
    public:
        using SceneObjectPtr = std::shared_ptr<SceneObject>;
        using CameraPtr = std::shared_ptr<Camera>;

    public:
        Scene(uint16_t width, uint16_t height);

        void add_object(const SceneObjectPtr& object);
        void set_camera(const CameraPtr& camera);


        uint16_t get_width() const;
        uint16_t get_height() const;

        Camera& get_camera() const;
        SceneObjectPtr intersect(const Ray& ray, IntersectionInfo& info) const;

    private:
        uint16_t width_;
        uint16_t height_;

        CameraPtr camera_;
        std::forward_list<SceneObjectPtr> objects_;
    };
}