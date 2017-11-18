#pragma once


#include <vector>
#include <dcdr/scene/ISceneObject.h>
#include <dcdr/scene/Camera.h>
#include <dcdr/utils/Iterator.h>

namespace Dcdr::Scene
{
    class ISceneController
    {
    public:
        virtual void add_object(SceneObjectUniquePtr object) = 0;
        virtual void set_camera(CameraUniquePtr camera) = 0;

        virtual Utils::ConstIteratorPtr<ISceneObject> get_objects_iterator(const Tracing::Ray& ray) const = 0;

        virtual Camera& get_camera() const = 0;

        virtual SceneObjectPtr intersect(const Tracing::Ray& ray, Tracing::IntersectionInfo& info) const = 0;

        virtual ~ISceneController() = default;
    };

    typedef std::shared_ptr<ISceneController> SceneControllerPtr;
}