#pragma once

#include <cstdint>
#include <string>

namespace Dcdr::Interconnect::Commander
{
    enum class JobState : uint8_t
    {
        InProgress,
        Stopped,
        Removed
    };

    enum class NodeState : uint8_t
    {
        Active,
        Disabled,
        Malfunctioned,
        Offline
    };

    struct Job
    {
        uint32_t id;
        std::string name;
        JobState state;
    };

    struct PropertyPair
    {
        std::string name;
        std::string value;
    };

    struct Scene
    {
        uint32_t id;
        std::string name;
        uint16_t width;
        uint16_t height;
    };

    struct Node
    {
        uint32_t id;
        std::string name;
        NodeState state;
    };

    enum class CommanderErrorKind : uint16_t
    {
        JobNotExist,
        NodeNotExist,
        SceneNotExist
    };

    enum class ArtifactFormat : uint16_t
    {
        Rgb24Unsigned
    };
}