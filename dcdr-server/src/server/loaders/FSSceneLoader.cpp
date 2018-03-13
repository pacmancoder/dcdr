#include <dcdr/server/loaders/FSSceneLoader.h>
#include <dcdr/server/core/Scene.h>

#include <fstream>
#include <iostream>

using namespace Dcdr::Server;

FSSceneLoader::FSSceneLoader(const std::string& sceneCachePath) :
    sceneCachePath_(sceneCachePath) {}

void FSSceneLoader::load_scenes(SharedResourceManager<Scene> &scenes)
{
    // TODO: Replace with scene meta info parsing
    std::string indexPath (sceneCachePath_ + "/index.txt");
    std::ifstream index(indexPath);

    for (;;)
    {
        std::string scenePath;
        std::string sceneName;
        uint16_t width = 0, height = 0;

        index >> scenePath >> sceneName >> width >> height;

        if (!index)
        {
            break;
        }

        scenes.add(Scene(sceneCachePath_ + scenePath, sceneName, width, height));
    }
}

