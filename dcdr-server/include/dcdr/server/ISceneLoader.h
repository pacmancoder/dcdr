#pragma once

#include <map>

namespace Dcdr::Server
{
    class Scene;

    class ISceneLoader
    {
    public:
        virtual void load_scenes(std::map<uint32_t, Scene> scenes) = 0;

        virtual ~ISceneLoader() = default;
    };
}