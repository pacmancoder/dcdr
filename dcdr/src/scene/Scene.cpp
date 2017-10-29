#include <dcdr/scene/Scene.h>

using namespace Dcdr;
using namespace Dcdr::Scene;
using namespace Dcdr::Tracing;
using namespace Dcdr::Utils;

namespace Dcdr::Scene
{
    class SceneObjectsIterator : public IConstIterator<ISceneObject>
    {
    public:
        explicit SceneObjectsIterator(const Dcdr::Scene::Scene& scene) :
                scene_(scene),
                cbegin(scene.objects_.cbegin()),
                cend(scene.objects_.cend()) {}

        void advance() override { ++cbegin; }

        bool can_advance() override { return cbegin != cend; }

        const ISceneObject& get() override
        {
            return *cbegin->second;
        }
    private:
        const Dcdr::Scene::Scene& scene_;
        std::map<SceneObjectId, SceneObjectPtr>::const_iterator cbegin;
        std::map<SceneObjectId, SceneObjectPtr>::const_iterator cend;
    };
}

void Scene::Scene::add_object(const SceneObjectId& id, SceneObjectUniquePtr object)
{
    objects_[id] = std::move(object);
}

void Scene::Scene::set_camera(CameraUniquePtr camera)
{
    camera_ = std::move(camera);
}

ISceneObject& Scene::Scene::get_object(const SceneObjectId&  id) const
{
    return *objects_.at(id);
}

Camera& Scene::Scene::get_camera() const
{
    return *camera_;
}

void Scene::Scene::get_objects_id_list(std::vector<SceneObjectId>& objects) const
{
    objects.clear();
    for (const auto& object : objects_)
    {
        objects.push_back(object.first);
    }
}

const std::shared_ptr<ISceneObject> Scene::Scene::intersect(const Ray& ray, IntersectionInfo& info) const
{
    for (const auto& object : objects_)
    {
        bool hit = object.second->intersect(ray, info);
        if (hit)
        {
            return object.second;
        }
    }
    return nullptr;
}

Utils::ConstIteratorPtr<ISceneObject> Scene::Scene::get_objects_iterator(const Ray& ray) const
{
    return ConstIteratorPtr<ISceneObject>(new SceneObjectsIterator(*this));
}