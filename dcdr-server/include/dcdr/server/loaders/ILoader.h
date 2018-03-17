#pragma once

#include <map>

#include <dcdr/server/core/CoreContext.h>

namespace Dcdr::Server
{
    class Scene;

    class ILoader
    {
    public:
        virtual void load(CoreContext& context) = 0;

        virtual ~ILoader() = default;
    };
}