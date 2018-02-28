#pragma once

// Include implicitly -- Worker Types are subset of Interconnect Types
#include <dcdr/messaging/InterconnectTypes.h>

#include <vector>

namespace Dcdr::Interconnect::Worker
{
    enum class ServerStatus : uint16_t
    {
        Ok,
        NodeNotConnected,
        TaskNotExist,
        SceneNotExist,
        WrongSceneOffset
    };

    struct TaskArtifact
    {
        uint32_t taskId;
        std::vector<uint8_t> data;
    };

    struct ChunkTaskInfo
    {
        uint32_t taskId;

        uint32_t sceneId;
        uint16_t sceneWidth;
        uint16_t sceneHeight;

        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        uint32_t minIterations;
        uint32_t maxIterations;
    };
}