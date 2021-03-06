#pragma once

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>
#include <dcdr/messaging/worker/WorkerInterconnectTypes.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

#include <vector>

namespace Dcdr::Interconnect::FlatBuffers::DeserializerUtils
{
    Commander::JobState marshal(DcdrFlatBuffers::JobState jobState);
    Commander::NodeState marshal(DcdrFlatBuffers::NodeState nodeState);
    Commander::CommanderErrorKind marshal(DcdrFlatBuffers::CommanderErrorKind errorKind);
    Commander::ArtifactFormat marshal(DcdrFlatBuffers::ArtifactFormat artifactFormat);

    Worker::ServerStatus marshal(DcdrFlatBuffers::WorkerServerStatus status);

    PropertyPair deserialize(const DcdrFlatBuffers::PropertyPair* job);

    Commander::Job deserialize(const DcdrFlatBuffers::Job* job);
    Commander::Node deserialize(const DcdrFlatBuffers::Node* node);
    Commander::Scene deserialize(const DcdrFlatBuffers::Scene* scene);

    Worker::Pixel deserialize(const DcdrFlatBuffers::Pixel* pixel);
    Worker::TaskArtifact deserialize(const DcdrFlatBuffers::TaskArtifact* taskArtifact);
    Worker::TaskInfo deserialize(const DcdrFlatBuffers::TaskInfo* taskInfo);


    template <class From, class To>
    std::vector<To> deserialize_vector(const flatbuffers::Vector<flatbuffers::Offset<From>>* data)
    {
        std::vector<To> vec;

        for (auto i = data->begin(); i != data->end(); ++i)
        {
            vec.push_back(deserialize(*i));
        }

        return vec;
    };
}