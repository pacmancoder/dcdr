#pragma once

#include <dcdr/server/ISceneLoader.h>

namespace Dcdr::Server
{
    class DummySceneLoader : public ISceneLoader
    {
    public:
        void load_scenes(std::map<uint32_t, Scene> scenes) override;
    };
}