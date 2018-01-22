#pragma once

#include <dcdr/messaging/AParcelSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{

    class FlatBuffersParcelSerializer : public AParcelSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const WorkerConnectRequest& parcel) override;
    };
}