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
        case Commander::CommanderErrorKind::Ok:            return DcdrFlatBuffers::CommanderErrorKind_Ok;
        case Commander::CommanderErrorKind::JobNotExist:   return DcdrFlatBuffers::CommanderErrorKind_JobNotExist;
        case Commander::CommanderErrorKind::NodeNotExist:  return DcdrFlatBuffers::CommanderErrorKind_NodeNotExist;
        case Commander::CommanderErrorKind::SceneNotExist: return DcdrFlatBuffers::CommanderErrorKind_SceneNotExist;
    }

    throw std::invalid_argument("Unreachable code");
}

DcdrFlatBuffers::ArtifactFormat SerializerUtils::marshal(Commander::ArtifactFormat artifactFormat)
{
    switch (artifactFormat)
    {
        case Commander::ArtifactFormat::Rgb24Unsigned: return DcdrFlatBuffers::ArtifactFormat_Rgb24Unsigned;
    }

    throw std::invalid_argument("Unreachable code");
}

DcdrFlatBuffers::WorkerServerStatus SerializerUtils::marshal(Worker::ServerStatus status)
{
    switch (status)
    {
        case Worker::ServerStatus::Ok:
            return DcdrFlatBuffers::WorkerServerStatus::WorkerServerStatus_Ok;
        case Worker::ServerStatus::NodeNotConnected:
            return DcdrFlatBuffers::WorkerServerStatus::WorkerServerStatus_NodeNotConnected;
        case Worker::ServerStatus::SceneNotExist:
            return DcdrFlatBuffers::WorkerServerStatus::WorkerServerStatus_SceneNotExist;
        case Worker::ServerStatus::TaskNotExist:
            return DcdrFlatBuffers::WorkerServerStatus::WorkerServerStatus_TaskNotExist;
        case Worker::ServerStatus::WrongSceneOffset:
            return DcdrFlatBuffers::WorkerServerStatus::WorkerServerStatus_WrongSceneOffset;
    }

    throw std::invalid_argument("Unreachable code");
}

flatbuffers::Offset<DcdrFlatBuffers::Job>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Job& job)
{
    return DcdrFlatBuffers::CreateJob(builder, job.id, builder.CreateString(job.name), marshal(job.state));
}

flatbuffers::Offset<DcdrFlatBuffers::PropertyPair>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const PropertyPair& propertyPair)
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

flatbuffers::Offset<DcdrFlatBuffers::Pixel>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Worker::Pixel& pixel)
{
    return DcdrFlatBuffers::CreatePixel(builder, pixel.color.r, pixel.color.g, pixel.color.b, pixel.samples);
}

flatbuffers::Offset<DcdrFlatBuffers::TaskArtifact>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder& builder, const Worker::TaskArtifact& taskArtifact)
{
    return DcdrFlatBuffers::CreateTaskArtifact(
            builder,
            taskArtifact.taskId,
            serialize_vector<Worker::Pixel, DcdrFlatBuffers::Pixel>(builder, taskArtifact.data));
}

flatbuffers::Offset<DcdrFlatBuffers::TaskInfo>
SerializerUtils::serialize(flatbuffers::FlatBufferBuilder &builder, const Worker::TaskInfo &taskInfo)
{
    return DcdrFlatBuffers::CreateTaskInfo(
            builder,
            taskInfo.taskId,
            taskInfo.sceneId,
            taskInfo.x,
            taskInfo.y,
            taskInfo.width,
            taskInfo.height,
            taskInfo.minIterations,
            taskInfo.maxIterations
    );
}
