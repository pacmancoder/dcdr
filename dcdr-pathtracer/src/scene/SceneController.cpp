#include <dcdr/scene/SceneController.h>

using namespace Dcdr;
using namespace Dcdr::Scene;
using namespace Dcdr::Tracing;
using namespace Dcdr::Utils;

namespace Dcdr::Scene
{
    class SceneObjectsIterator : public IConstIterator<ISceneObject>
    {
    public:
        explicit SceneObjectsIterator(const Dcdr::Scene::SceneController& scene) :
                current(scene.objects_.cbegin()),
                end(scene.objects_.cend()) {}

        void advance() override { ++current; }

        bool can_advance() override { return current != end; }

        const ISceneObject& get() override
        {
            return *(current->get());
        }
    private:
        std::vector<SceneObjectPtr>::const_iterator current;
        std::vector<SceneObjectPtr>::const_iterator end;
    };
}

void SceneController::SceneController::add_object(SceneObjectUniquePtr object)
{
    objects_.push_back(std::move(object));
}

void SceneController::SceneController::set_camera(CameraUniquePtr camera)
{
    camera_ = std::move(camera);
}

Camera& SceneController::SceneController::get_camera() const
{
    return *camera_;
}


SceneObjectPtr SceneController::SceneController::intersect(const Ray& ray, IntersectionInfo& info) const
{
    for (const auto& object : objects_)
    {
        bool hit = object->intersect(ray, info);
        if (hit)
        {
            return object;
        }
    }
    return nullptr;
}

Utils::ConstIteratorPtr<ISceneObject> SceneController::SceneController::get_objects_iterator(const Ray& ray) const
{
    return ConstIteratorPtr<ISceneObject>(new SceneObjectsIterator(*this));
}