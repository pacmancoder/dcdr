#pragma once

#include <string>
#include <microtar.h>
#include <dcdr/server/loaders/ISceneLoader.h>

namespace Dcdr::Server
{
    class FSSceneLoader : public ISceneLoader
    {
    public:
        explicit FSSceneLoader(const std::string& sceneCachePath);
        void load_scenes(SharedResourceManager<Scene> &scenes) override;

    private:
        std::string sceneCachePath_;
    };
}
