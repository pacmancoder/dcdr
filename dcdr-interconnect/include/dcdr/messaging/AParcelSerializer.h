#pragma once

#include <vector>
#include <cstdint>

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class WorkerConnectRequest;

    class CommanderGetSurfaceInfoRequest;
    class CommanderGetSurfaceRequest;

    class CommanderGetSurfaceInfoResponse;
    class CommanderGetSurfaceResponse;

    class AParcelSerializer
    {
    public:
        // === Worker parcels ===
        virtual IParcel::SerializedParcel serialize(const WorkerConnectRequest& parcel);

        // === Core parcels ===
        virtual IParcel::SerializedParcel serialize(const CommanderGetSurfaceRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoRequest& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoResponse& parcel);
        virtual IParcel::SerializedParcel serialize(const CommanderGetSurfaceResponse& parcel);

        virtual ~AParcelSerializer() = default;

    protected:
        virtual IParcel::SerializedParcel serialize_not_supported();

    };
}
