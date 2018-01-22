#include <dcdr/messaging/AParcelDeserializer.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelPtr AParcelDeserializer::deserialize_not_supported()
{
    return nullptr;
}