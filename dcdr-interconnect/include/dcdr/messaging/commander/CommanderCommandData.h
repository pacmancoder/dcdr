#pragma once

#include <cstdint>

namespace Dcdr::Interconnect
{
    enum class JobState : uint8_t
    {
        InProgress,
        Stopped,
        Removed,
    };

    enum class NodeState : uint8_t
    {
        Active,
        Disabled,
        Malfunctioned,
        Offline,
    };
}