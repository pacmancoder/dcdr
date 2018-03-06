#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/logging/Logger.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>
#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

#include <vector>
#include <dcdr/messaging/worker/WorkerInterconnectTypes.h>

// Following template classes should be local to cpp in which they were included
namespace Dcdr::Interconnect::FlatBuffers::SerializerUtils
{
    template <class ParcelType, class ParcelGenerator>
    IParcel::SerializedParcel build_parcel(ParcelGenerator&& parcelGenerator, size_t builderBufferSize);

    DcdrFlatBuffers::JobState marshal(Commander::JobState jobState);
    DcdrFlatBuffers::NodeState marshal(Commander::NodeState nodeState);
    DcdrFlatBuffers::CommanderErrorKind marshal(Commander::CommanderErrorKind errorKind);
    DcdrFlatBuffers::ArtifactFormat marshal(Commander::ArtifactFormat artifactFormat);

    DcdrFlatBuffers::WorkerServerStatus marshal(Worker::ServerStatus status);

    flatbuffers::Offset<DcdrFlatBuffers::PropertyPair> serialize(flatbuffers::FlatBufferBuilder& builder, const PropertyPair& propertyPair);

    flatbuffers::Offset<DcdrFlatBuffers::Job> serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Job& job);
    flatbuffers::Offset<DcdrFlatBuffers::Scene> serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Scene& scene);
    flatbuffers::Offset<DcdrFlatBuffers::Node> serialize(flatbuffers::FlatBufferBuilder& builder, const Commander::Node& node);

    flatbuffers::Offset<DcdrFlatBuffers::Pixel> serialize(flatbuffers::FlatBufferBuilder& builder, const Worker::Pixel& pixel);
    flatbuffers::Offset<DcdrFlatBuffers::TaskArtifact> serialize(flatbuffers::FlatBufferBuilder& builder, const Worker::TaskArtifact& taskArtifact);
    flatbuffers::Offset<DcdrFlatBuffers::TaskInfo> serialize(flatbuffers::FlatBufferBuilder& builder, const Worker::TaskInfo& taskInfo);

    template <class From, class To>
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<To>>> serialize_vector(
            flatbuffers::FlatBufferBuilder& builder, const std::vector<From>& data)
    {
        std::vector<flatbuffers::Offset<To>> offsets;
        for(const auto& i : data)
        {
            offsets.push_back(serialize(builder, i));
        }

        return builder.CreateVector(offsets);
    }

    // === Template Implementations ===

    template <class ParcelType, class ParcelGenerator>
    IParcel::SerializedParcel build_parcel(ParcelGenerator&& parcelGenerator, size_t builderBufferSize)
    {
        using namespace Dcdr::Logging;

        const char* LOG_PREFIX =  "[Interconnect][FlatBuffers] ";

        log_trace(LOG_PREFIX, "Building ", ParcelType::GetFullyQualifiedName());

        flatbuffers::FlatBufferBuilder flatBuffersBuilder(builderBufferSize);

        flatbuffers::Offset<ParcelType> parcelData = std::forward<ParcelGenerator>(parcelGenerator)(flatBuffersBuilder);

        auto parcel = DcdrFlatBuffers::CreateParcel(
                flatBuffersBuilder,
                DcdrFlatBuffers::ParcelDataTraits<ParcelType>::enum_value,
                parcelData.Union());

        flatBuffersBuilder.Finish(parcel);

        log_trace(LOG_PREFIX, ParcelType::GetFullyQualifiedName(), " flatbuffer was created");

        return IParcel::SerializedParcel(
                flatBuffersBuilder.GetBufferPointer(),
                flatBuffersBuilder.GetBufferPointer() + flatBuffersBuilder.GetSize());
    }
}