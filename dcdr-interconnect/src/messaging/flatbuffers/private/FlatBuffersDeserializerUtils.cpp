#include "FlatBuffersDeserializerUtils.h"

#include <stdexcept>

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

Commander::JobState DeserializerUtils::marshal(DcdrFlatBuffers::JobState jobState)
{
    switch (jobState)
    {
        case DcdrFlatBuffers::JobState_InProgress: return Commander::JobState::InProgress;
        case DcdrFlatBuffers::JobState_Stopped:    return  Commander::JobState::Stopped;
        case DcdrFlatBuffers::JobState_Removed:    return Commander::JobState::Removed;
    }

    throw std::invalid_argument("<Unreachable code>");
}

Commander::NodeState DeserializerUtils::marshal(DcdrFlatBuffers::NodeState nodeState)
{
    switch (nodeState)
    {
        case DcdrFlatBuffers::NodeState_Active:        return Commander::NodeState::Active;
        case DcdrFlatBuffers::NodeState_Disabled:      return Commander::NodeState::Disabled;
        case DcdrFlatBuffers::NodeState_Malfunctioned: return Commander::NodeState::Malfunctioned;
        case DcdrFlatBuffers::NodeState_Offline:       return Commander::NodeState::Offline;
    }

    throw std::invalid_argument("<Unreachable code>");
}

Commander::CommanderErrorKind DeserializerUtils::marshal(DcdrFlatBuffers::CommanderErrorKind errorKind)
{
    switch (errorKind)
    {
        case DcdrFlatBuffers::CommanderErrorKind_JobNotExist:   return Commander::CommanderErrorKind::JobNotExist;
        case DcdrFlatBuffers::CommanderErrorKind_NodeNotExist:  return Commander::CommanderErrorKind::NodeNotExist;
        case DcdrFlatBuffers::CommanderErrorKind_SceneNotExist: return Commander::CommanderErrorKind::SceneNotExist;
    }

    throw std::invalid_argument("<Unreachable code>");
}

Commander::ArtifactFormat DeserializerUtils::marshal(DcdrFlatBuffers::ArtifactFormat artifactFormat)
{
    switch (artifactFormat)
    {
        case DcdrFlatBuffers::ArtifactFormat_Rgb24Unsigned: return Commander::ArtifactFormat::Rgb24Unsigned;
    }

    throw std::invalid_argument("<Unreachable code>");
}

Commander::Job DeserializerUtils::deserialize(const DcdrFlatBuffers::Job* job)
{
    return Commander::Job { job->id(), job->name()->str(), marshal(job->state()) };
}

Commander::Node DeserializerUtils::deserialize(const DcdrFlatBuffers::Node* node)
{
    return Commander::Node { node->id(), node->name()->str(), marshal(node->state()) };
}

Commander::Scene DeserializerUtils::deserialize(const DcdrFlatBuffers::Scene* scene)
{
    return Commander::Scene { scene->id(), scene->name()->str(), scene->width(), scene->height() };
}

PropertyPair DeserializerUtils::deserialize(const DcdrFlatBuffers::PropertyPair* job)
{
    return PropertyPair { job->name()->str(), job->value()->str() };
}
