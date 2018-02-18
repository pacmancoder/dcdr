#include <dcdr/server/loaders/DummySceneLoader.h>

#include <dcdr/server/core/Scene.h>

using namespace Dcdr::Server;

void DummySceneLoader::load_scenes(SharedResourceManager<Scene>& scenes)
{
    scenes.add(Scene("cornell.dspf"));
    scenes.add(Scene("spheres.dspf"));
}
