#include "FlatBuffersDeserializerUtils.h"

#include <stdexcept>

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

Commander::JobState DeserializerUtils::marshal(DcdrFlatBuffers::JobState jobState)
{
    switch (jobState)
    {
        case DcdrFlatBuffers::JobState_InProgress: return Commander::JobState::InProgress;
        case DcdrFlatBuffers::JobState_Stopped: return  Commander::JobState::Stopped;
        case DcdrFlatBuffers::JobState_Removed: return Commander::JobState::Removed;
    }

    throw std::invalid_argument("<Unreachable code>");
}

Commander::NodeState DeserializerUtils::marshal(DcdrFlatBuffers::NodeState nodeState)
{
    switch (nodeState)
    {
        case DcdrFlatBuffers::NodeState_Active: return Commander::NodeState::Active;
        case DcdrFlatBuffers::NodeState_Disabled: return Commander::NodeState::Disabled;
        case DcdrFlatBuffers::NodeState_Malfunctioned: return Commander::NodeState::Malfunctioned;
        case DcdrFlatBuffers::NodeState_Offline: return Commander::NodeState::Offline;
    }

    throw std::invalid_argument("<Unreachable code>");
}