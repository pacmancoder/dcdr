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

DcdrFlatBuffers::CommanderErrorKind SerializerUtils::marshal(Commander::CommanderErrorKind errorKind)
{
    switch (errorKind)
    {
        case Commander::CommanderErrorKind::JobNotExist:   return DcdrFlatBuffers::CommanderErrorKind_JobNotExist;
        case Commander::CommanderErrorKind::NodeNotExist:  return DcdrFlatBuffers::CommanderErrorKind_NodeNotExist;
        case Commander::CommanderErrorKind::SceneNotExist: return DcdrFlatBuffers::CommanderErrorKind_SceneNotExist;
    }

    throw std::invalid_argument("Unreachable code");
}


flatbuffers::Offset<DcdrFlatBuffers::Job>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Job& job)
{
    return DcdrFlatBuffers::CreateJob(builder, job.id, builder.CreateString(job.name), marshal(job.state));
}

flatbuffers::Offset<DcdrFlatBuffers::PropertyPair>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::PropertyPair& propertyPair)
{
    return DcdrFlatBuffers::CreatePropertyPair(
            builder, builder.CreateString(propertyPair.name), builder.CreateString(propertyPair.value));
}

flatbuffers::Offset<DcdrFlatBuffers::Scene>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Scene& scene)
{
    return DcdrFlatBuffers::CreateScene(builder, scene.id, builder.CreateString(scene.name), scene.width, scene.height);
}

flatbuffers::Offset<DcdrFlatBuffers::Node>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Node& node)
{
    return DcdrFlatBuffers::CreateNode(builder, node.id, builder.CreateString(node.name), marshal(node.state));
}
