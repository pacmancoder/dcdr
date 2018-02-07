#include "FlatBuffersSerializerUtils.h"

#include <stdexcept>

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

DcdrFlatBuffers::JobState SerializerUtils::marshal(Commander::JobState jobState)
{
    switch (jobState)
    {
        case Commander::JobState::InProgress: return DcdrFlatBuffers::JobState_InProgress;
        case Commander::JobState::Stopped:    return DcdrFlatBuffers::JobState_Stopped;
        case Commander::JobState::Removed:    return DcdrFlatBuffers::JobState_Removed;
    }

    throw std::invalid_argument("Unreachable code");
}

DcdrFlatBuffers::NodeState SerializerUtils::marshal(Commander::NodeState nodeState)
{
    switch (nodeState)
    {
        case Commander::NodeState::Active:        return DcdrFlatBuffers::NodeState_Active;
        case Commander::NodeState::Disabled:      return DcdrFlatBuffers::NodeState_Disabled;
        case Commander::NodeState::Malfunctioned: return DcdrFlatBuffers::NodeState_Malfunctioned;
        case Commander::NodeState::Offline:       return DcdrFlatBuffers::NodeState_Offline;
    }

    throw std::invalid_argument("Unreachable code");
}