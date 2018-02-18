#include <dcdr/server/DummySceneLoader.h>

#include <dcdr/server/Scene.h>

using namespace Dcdr::Server;

void DummySceneLoader::load_scenes(std::map<uint32_t, Scene> scenes)
{
    scenes.emplace(0, Scene("cornell.dspf"));
    scenes.emplace(1, Scene("spheres.dspf"));
}
