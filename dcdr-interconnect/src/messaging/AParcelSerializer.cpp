#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;


// Definition generator to avoid boilerplate code
#define SERIALIZATION_NOT_IMPLEMENTED(__TARGET_CLASS__) \
    IParcel::SerializedParcel AParcelSerializer::serialize(const __TARGET_CLASS__&)\
    {\
        return serialize_not_supported();\
    }\


// default behavior - return empty parcel serialization
IParcel::SerializedParcel AParcelSerializer::serialize_not_supported() { return IParcel::SerializedParcel(); }

SERIALIZATION_NOT_IMPLEMENTED(WorkerConnectRequest);

SERIALIZATION_NOT_IMPLEMENTED(CommanderGetSurfaceRequest)
SERIALIZATION_NOT_IMPLEMENTED(CommanderGetSurfaceInfoRequest)
SERIALIZATION_NOT_IMPLEMENTED(CommanderGetSurfaceResponse)
SERIALIZATION_NOT_IMPLEMENTED(CommanderGetSurfaceInfoResponse)