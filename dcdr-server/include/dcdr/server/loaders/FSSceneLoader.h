#pragma once

#include <string>
#include <dcdr/server/loaders/ILoader.h>

namespace Dcdr::Server
{
    class FSSceneLoader : public ILoader
    {
    public:
        explicit FSSceneLoader(const std::string& sceneCachePath);
        void load(CoreContext& context) override;

    private:
        std::string sceneCachePath_;
    };
}
