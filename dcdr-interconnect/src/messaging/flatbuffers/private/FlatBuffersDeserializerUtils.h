#pragma once

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

#include <vector>

namespace Dcdr::Interconnect::FlatBuffers::DeserializerUtils
{
    Commander::JobState marshal(DcdrFlatBuffers::JobState jobState);
    Commander::NodeState marshal(DcdrFlatBuffers::NodeState nodeState);
    Commander::CommanderErrorKind marshal(DcdrFlatBuffers::CommanderErrorKind errorKind);
    Commander::ArtifactFormat marshal(DcdrFlatBuffers::ArtifactFormat artifactFormat);

    Commander::Job deserialize(const DcdrFlatBuffers::Job* job);
    Commander::Node deserialize(const DcdrFlatBuffers::Node* job);
    Commander::Scene deserialize(const DcdrFlatBuffers::Scene* job);
    Commander::PropertyPair deserialize(const DcdrFlatBuffers::PropertyPair* job);

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