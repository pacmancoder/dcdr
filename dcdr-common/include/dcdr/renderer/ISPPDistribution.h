#pragma once

#include <dcdr/Types.h>

namespace Dcdr
{
    class ISPPDistribution
    {
    public:
        virtual Types::Counter get_samples_count(Types::Vec3 colorStandardDerivation) const = 0;

        virtual ~ISPPDistribution() = default;
    };
}