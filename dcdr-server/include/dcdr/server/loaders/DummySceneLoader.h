#pragma once

#include <dcdr/server/loaders/ISceneLoader.h>

namespace Dcdr::Server
{
    class DummySceneLoader : public ISceneLoader
    {
    public:
        void load_scenes(SharedResourceManager<Scene>& scenes) override;
    };
}