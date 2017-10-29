#pragma once


#include <vector>
#include <dcdr/scene/ISceneObject.h>
#include <dcdr/scene/Camera.h>
#include <dcdr/utils/Iterator.h>

namespace Dcdr::Scene
{
    class IScene
    {
    public:
        virtual void add_object(const SceneObjectId& , SceneObjectUniquePtr object) = 0;
        virtual void set_camera(CameraUniquePtr camera) = 0;

        virtual ISceneObject& get_object(const Scene::SceneObjectId& ) const = 0;
        virtual Utils::ConstIteratorPtr<ISceneObject> get_objects_iterator(const Tracing::Ray& ray) const = 0;

        virtual Camera& get_camera() const = 0;

        virtual void get_objects_id_list(std::vector<SceneObjectId>& objects) const = 0;

        virtual const std::shared_ptr<ISceneObject>
            intersect(const Tracing::Ray& ray, Tracing::IntersectionInfo& info) const = 0;
    };

    typedef std::shared_ptr<IScene> ScenePtr;
}