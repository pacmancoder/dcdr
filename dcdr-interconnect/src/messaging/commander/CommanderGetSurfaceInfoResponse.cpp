#include <dcdr/messaging/commander/CommanderGetSurfaceInfoResponse.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

void CommanderGetSurfaceInfoResponse::set_width(uint32_t width) { width_ = width; }
void CommanderGetSurfaceInfoResponse::set_height(uint32_t height) { height_ = height; }

uint32_t CommanderGetSurfaceInfoResponse::get_width() const { return width_; }
uint32_t CommanderGetSurfaceInfoResponse::get_height() const { return height_; }


IParcel::SerializedParcel CommanderGetSurfaceInfoResponse::serialize(AParcelSerializer& serializer) const
{
    return serializer.serialize(*this);
}
