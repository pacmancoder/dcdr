#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;


// Definition generator to avoid boilerplate code
#define IMPLEMENT_DEFAULT_SERIALIZATION(__TARGET_CLASS__) \
    IParcel::SerializedParcel AParcelSerializer::serialize(const __TARGET_CLASS__&)\
    {\
        return serialize_not_supported();\
    }\


// default behavior - return empty parcel serialization
IParcel::SerializedParcel AParcelSerializer::serialize_not_supported() { return IParcel::SerializedParcel(); }

IMPLEMENT_DEFAULT_SERIALIZATION(WorkerConnectRequest);

IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetJobListRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetJobInfoRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetJobPreviewRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetJobArtifactRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderSetJobStateRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderAddJobRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetSceneListRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetNodeListRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetNodeInfoRequest)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderSetNodeStateRequest)

IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetSurfaceResponse)
IMPLEMENT_DEFAULT_SERIALIZATION(CommanderGetSurfaceInfoResponse)