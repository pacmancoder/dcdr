#pragma once

#include <vector>
#include <cstdint>

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class WorkerConnectRequest;

    // commander job requests
    class CommanderGetJobListRequest;
    class CommanderGetJobInfoRequest;
    class CommanderGetJobPreviewRequest;
    class CommanderGetJobArtifactRequest;
    class CommanderSetJobStateRequest;
    class CommanderAddJobRequest;
    class CommanderGetSceneListRequest;
    // commander node requests
    class CommanderGetNodeListRequest;
    class CommanderGetNodeInfoRequest;
    class CommanderSetNodeStateRequest;

    class CommanderGetSurfaceInfoResponse;
    class CommanderGetSurfaceResponse;

    class AParcelSerializer
    {
    public:
        // === Worker parcels ===
        virtual IParcel::SerializedParcel serialize(const WorkerConnectRequest& parcel);

        // === Commander parcels ===
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobListRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobInfoRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobPreviewRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobArtifactRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderSetJobStateRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderAddJobRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetSceneListRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeListRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeInfoRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderSetNodeStateRequest& parcel);

        virtual IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoResponse& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetSurfaceResponse& parcel);

        // === Service parcels ===

        virtual ~AParcelSerializer() = default;

    protected:
        virtual IParcel::SerializedParcel serialize_not_supported();

    };
}
