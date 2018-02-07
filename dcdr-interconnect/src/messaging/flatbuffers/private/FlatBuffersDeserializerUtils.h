#pragma once

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

namespace Dcdr::Interconnect::FlatBuffers::DeserializerUtils
{
    Commander::JobState marshal(DcdrFlatBuffers::JobState jobState);
    Commander::NodeState marshal(DcdrFlatBuffers::NodeState nodeState);
}