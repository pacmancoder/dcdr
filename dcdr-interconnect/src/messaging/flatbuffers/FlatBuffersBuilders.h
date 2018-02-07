#pragma once

#include <flatbuffers-generated/DcdrFlatBuffers.h>
#include <dcdr/logging/Logger.h>

// Following template classes should be local to cpp in which they were included
namespace
{
    using namespace Dcdr::Interconnect;
    using namespace Dcdr::Logging;

    template <class ParcelType, class ParcelGenerator>
    IParcel::SerializedParcel build_parcel(ParcelGenerator&& parcelGenerator, size_t builderBufferSize)
    {
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