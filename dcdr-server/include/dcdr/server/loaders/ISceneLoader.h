#pragma once

#include <map>

#include <dcdr/server/core/SharedResourceManager.h>

namespace Dcdr::Server
{
    class Scene;

    class ISceneLoader
    {
    public:
        virtual void load_scenes(SharedResourceManager<Scene>& scenes) = 0;

        virtual ~ISceneLoader() = default;
    };
}