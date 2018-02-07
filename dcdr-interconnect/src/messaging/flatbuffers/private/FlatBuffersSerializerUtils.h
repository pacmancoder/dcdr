#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/logging/Logger.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>
#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

// Following template classes should be local to cpp in which they were included
namespace Dcdr::Interconnect::FlatBuffers::SerializerUtils
{
    template <class ParcelType, class ParcelGenerator>
    IParcel::SerializedParcel build_parcel(ParcelGenerator&& parcelGenerator, size_t builderBufferSize);

    DcdrFlatBuffers::JobState marshal(Commander::JobState jobState);
    DcdrFlatBuffers::NodeState marshal(Commander::NodeState nodeState);


    // === Template Implementations ===

    template <class ParcelType, class ParcelGenerator>
    IParcel::SerializedParcel build_parcel(ParcelGenerator&& parcelGenerator, size_t builderBufferSize)
    {
        using namespace Dcdr::Logging;

        log_debug(std::string()
                          .append("[Interconnect][FlatBuffers] Building ")
                          .append(ParcelType::GetFullyQualifiedName())
                          .append(" flatbuffer"));

        flatbuffers::FlatBufferBuilder flatBuffersBuilder(builderBufferSize);

        flatbuffers::Offset<ParcelType> parcelData = std::forward<ParcelGenerator>(parcelGenerator)(flatBuffersBuilder);

        auto parcel = DcdrFlatBuffers::CreateParcel(
                flatBuffersBuilder,
                DcdrFlatBuffers::ParcelDataTraits<ParcelType>::enum_value,
                parcelData.Union());

        flatBuffersBuilder.Finish(parcel);

        log_debug(std::string()
                          .append("[Interconnect][FlatBuffers] ")
                          .append(ParcelType::GetFullyQualifiedName())
                          .append(" flatbuffer was created"));

        return IParcel::SerializedParcel(
                flatBuffersBuilder.GetBufferPointer(),
                flatBuffersBuilder.GetBufferPointer() + flatBuffersBuilder.GetSize());
    }
}