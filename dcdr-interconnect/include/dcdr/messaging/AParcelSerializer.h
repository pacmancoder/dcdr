#pragma once

#include <vector>
#include <cstdint>

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class WorkerConnectRequest;

    class AParcelSerializer
    {
    public:
        virtual IParcel::SerializedParcel serialize(const WorkerConnectRequest& parcel);

        virtual ~AParcelSerializer() = default;

    protected:
        IParcel::SerializedParcel serialize_not_supported();

    };
}
