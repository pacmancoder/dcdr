#pragma once

#include <dcdr/renderer/Scene.h>

#include <string>
#include <memory>
#include <vector>

namespace Dcdr::Worker
{
    class SceneLoader
    {
    public:
        explicit SceneLoader(const std::string& path);
        void load_to(Renderer::Scene& scene);

        ~SceneLoader();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}