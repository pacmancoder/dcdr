#include <dcdr/server/loaders/FSSceneLoader.h>
#include <dcdr/server/core/Scene.h>

#include <fstream>
#include <iostream>

using namespace Dcdr::Server;

FSSceneLoader::FSSceneLoader(const std::string& sceneCachePath) :
    sceneCachePath_(sceneCachePath) {}

void FSSceneLoader::load(CoreContext& context)
{
    std::string indexPath (sceneCachePath_ + "/index.txt");
    std::ifstream index(indexPath);

    for (;;)
    {
        std::string sceneFileName;
        std::string sceneName;
        uint16_t width = 0, height = 0;

        index >> sceneFileName >> sceneName >> width >> height;

        if (!index)
        {
            break;
        }

        auto sceneFileId = context.get_shared_files().add(
                SharedFile(sceneCachePath_ + "/" + sceneFileName, SharedFile::AccessMode::Readonly));

        context.get_scenes().add(Scene(
                sceneFileName, sceneFileId, sceneName, width, height));
    }
}

