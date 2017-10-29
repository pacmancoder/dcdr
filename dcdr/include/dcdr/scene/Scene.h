#pragma once

#include <map>
#include <vector>
#include <memory>

#include <dcdr/Types.h>
#include <dcdr/scene/ISceneObject.h>
#include <dcdr/scene/IScene.h>
#include <dcdr/scene/Camera.h>
#include <dcdr/tracing/Ray.h>
#include <dcdr/tracing/IntersectionInfo.h>

namespace Dcdr::Scene
{
    class SceneObjectsIterator;

    class Scene : public IScene
    {
    public :
        void add_object(const SceneObjectId& , SceneObjectUniquePtr object) override;
        void set_camera(CameraUniquePtr camera) override;

        ISceneObject& get_object(const Dcdr::Scene::SceneObjectId& ) const override;

        Utils::ConstIteratorPtr<ISceneObject> get_objects_iterator(const Tracing::Ray& ray) const override;

        Camera& get_camera() const override;

        void get_objects_id_list(std::vector<SceneObjectId>& objects) const override;

        const SceneObjectPtr intersect(const Tracing::Ray& ray, Tracing::IntersectionInfo& info) const override;

        friend class SceneObjectsIterator;
    private:
        std::map<SceneObjectId, SceneObjectPtr> objects_;
        CameraUniquePtr camera_;
    };
}