#include "FlatBuffersCommanderResponseSerializer.h"

#include <dcdr/messaging/commander/CommanderResponses.h>
#include <dcdr/logging/Logger.h>

#include "FlatBuffersSerializerUtils.h"

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    const char* LOG_PREFIX = "[Interconnect][FlatBuffers] ";
    const size_t COMMANDER_RESPONSE_BUILDER_BUFFER_SIZE = 1024;

    template <class ResponseType, class ParcelGenerator>
    IParcel::SerializedParcel build_commander_response_parcel(ParcelGenerator&& parcelGenerator)
    {
        return SerializerUtils::build_parcel<DcdrFlatBuffers::CommanderResponse>(
                [parcelGenerator=std::forward<ParcelGenerator>(parcelGenerator)] (auto& flatBuffersBuilder)
                {
                    log_trace(LOG_PREFIX, "Serializing parcel into ", ResponseType::GetFullyQualifiedName());

                    flatbuffers::Offset<ResponseType> responseData = parcelGenerator(flatBuffersBuilder);

                    log_trace(LOG_PREFIX, "Parcel was serialized to ", ResponseType::GetFullyQualifiedName());

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
                        SerializerUtils::serialize_vector<PropertyPair, DcdrFlatBuffers::PropertyPair>(
                                flatBuffersBuilder, parcel.get_job_info()));
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
                        SerializerUtils::marshal(parcel.get_format()),
                        parcel.get_width(),
                        parcel.get_height(),
                        flatBuffersBuilder.CreateVector(parcel.get_data()));
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
                        SerializerUtils::serialize_vector<PropertyPair, DcdrFlatBuffers::PropertyPair>(
                                flatBuffersBuilder, parcel.get_node_info()));
            });
}

IParcel::SerializedParcel FlatBuffersCommanderResponseSerializer::serialize(const CommanderErrorResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderErrorResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderErrorResponse(
                        flatBuffersBuilder,
                        SerializerUtils::marshal(parcel.get_error_kind()),
                        flatBuffersBuilder.CreateString(parcel.get_message()));
            });
}

IParcel::SerializedParcel
FlatBuffersCommanderResponseSerializer::serialize(const CommanderGetServerStatusResponse& parcel)
{
    return build_commander_response_parcel<DcdrFlatBuffers::CommanderGetServerStatusResponse>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetServerStatusResponse(
                        flatBuffersBuilder,
                        parcel.get_scenes_last_modified_timestamp(),
                        parcel.get_jobs_last_modified_timestamp(),
                        parcel.get_nodes_last_modified_timestamp());
            });
}
