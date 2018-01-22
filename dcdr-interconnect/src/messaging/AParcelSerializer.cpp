#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::SerializedParcel AParcelSerializer::serialize_not_supported()
{
    return IParcel::SerializedParcel();
}

IParcel::SerializedParcel AParcelSerializer::serialize(const WorkerConnectRequest& parcel)
{
    return serialize_not_supported();
}
