#pragma once

#include <vector>
#include <memory>

#include <dcdr/Types.h>
#include <dcdr/scene/ISceneObject.h>
#include <dcdr/scene/ISceneController.h>
#include <dcdr/scene/Camera.h>
#include <dcdr/tracing/Ray.h>
#include <dcdr/tracing/IntersectionInfo.h>

namespace Dcdr::Scene
{
    class SceneObjectsIterator;

    class SceneController : public ISceneController
    {
    public :
        void add_object(SceneObjectUniquePtr object) override;
        void set_camera(CameraUniquePtr camera) override;

        Utils::ConstIteratorPtr<ISceneObject> get_objects_iterator(const Tracing::Ray& ray) const override;

        Camera& get_camera() const override;

        SceneObjectPtr intersect(const Tracing::Ray& ray, Tracing::IntersectionInfo& info) const override;

        friend class SceneObjectsIterator;

    private:
        std::vector<SceneObjectPtr> objects_;
        CameraUniquePtr camera_;
    };
}