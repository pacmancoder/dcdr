#include "FlatBuffersCommanderResponseSerializer.h"

#include <dcdr/messaging/commander/CommanderResponses.h>
#include <dcdr/logging/Logger.h>

#include "FlatBuffersSerializerUtils.h"

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    const size_t COMMANDER_RESPONSE_BUILDER_BUFFER_SIZE = 1024;

    template <class ResponseType, class ParcelGenerator>
    IParcel::SerializedParcel build_commander_response_parcel(ParcelGenerator&& parcelGenerator)
    {
        return SerializerUtils::build_parcel<DcdrFlatBuffers::CommanderResponse>(
                [parcelGenerator=std::forward<ParcelGenerator>(parcelGenerator)] (auto& flatBuffersBuilder)
                {
                    log_debug(std::string()
                                      .append("[Interconnect][FlatBuffers] Serializing parcel into ")
                                      .append(ResponseType::GetFullyQualifiedName())
                                      .append(" flatbuffer"));

                    flatbuffers::Offset<ResponseType> responseData = parcelGenerator(flatBuffersBuilder);

                    log_debug(std::string()
                                      .append("[Interconnect][FlatBuffers] Parcel was serialized to ")
                                      .append(ResponseType::GetFullyQualifiedName())
                                      .append(" flatbuffer"));

                    return DcdrFlatBuffers::CreateCommanderResponse(
                            flatBuffersBuilder,
                            DcdrFlatBuffers::CommanderResponseDataTraits<ResponseType>::enum_value,
                            responseData.Union());
                },
                COMMANDER_RESPONSE_BUILDER_BUFFER_SIZE);
    }
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetJobListResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetJobListResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobListResponse(
                        flatBuffersBuilder,
                        SerializerUtils::serialize_vector<Commander::Job, DcdrFlatBuffers::Job>(
                                flatBuffersBuilder, parcel.get_jobs()));
            });
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetJobInfoResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetJobInfoResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobInfoResponse(
                        flatBuffersBuilder,
                        parcel.get_job_id(),
                        SerializerUtils::serialize_vector<Commander::PropertyPair, DcdrFlatBuffers::PropertyPair>(
                                flatBuffersBuilder, parcel.get_job_info()));
            });
}

IParcel::SerializedParcel
FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetJobPreviewResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetJobPreviewResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobPreviewResponse(
                        flatBuffersBuilder,
                        parcel.get_job_id(),
                        flatBuffersBuilder.CreateVector(parcel.get_preview()));
            });
}

IParcel::SerializedParcel
FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetJobArtifactResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetJobArtifactResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobArtifactResponse(
                        flatBuffersBuilder,
                        parcel.get_job_id(),
                        flatBuffersBuilder.CreateVector(parcel.get_artifact()));
            });
}

IParcel::SerializedParcel
FlatBuffersCommanderResponseSerializer::serialize(const CommanderDoJobListUpdateResponse&)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderDoJobListUpdateResponse>(
            [](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderDoJobListUpdateResponse(flatBuffersBuilder);
            });
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetSceneListResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetSceneListReponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetSceneListReponse(
                        flatBuffersBuilder,
                        SerializerUtils::serialize_vector<Commander::Scene, DcdrFlatBuffers::Scene>(
                                flatBuffersBuilder, parcel.get_scenes()));
            });
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetNodeListResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetNodeListResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetNodeListResponse(
                        flatBuffersBuilder,
                        SerializerUtils::serialize_vector<Commander::Node, DcdrFlatBuffers::Node>(
                                flatBuffersBuilder, parcel.get_nodes()));
            });
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetNodeInfoResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetNodeInfoResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetNodeInfoResponse(
                        flatBuffersBuilder,
                        parcel.get_node_id(),
                        SerializerUtils::serialize_vector<Commander::PropertyPair, DcdrFlatBuffers::PropertyPair>(
                                flatBuffersBuilder, parcel.get_node_info()));
            });
}

IParcel::SerializedParcel
FlatBuffersCommanderResponseSerializer::serialize(const CommanderDoNodeListUpdateResponse&)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderDoNodeListUpdateResponse>(
            [](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderDoNodeListUpdateResponse(flatBuffersBuilder);
            });
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderDoShowErrorResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderDoShowErrorResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderDoShowErrorResponse(
                        flatBuffersBuilder,
                        SerializerUtils::marshal(parcel.get_error_kind()),
                        flatBuffersBuilder.CreateString(parcel.get_message()));
            });
}
