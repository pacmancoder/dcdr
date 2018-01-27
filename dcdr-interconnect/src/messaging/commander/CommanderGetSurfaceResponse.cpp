#include <dcdr/messaging/commander/CommanderGetSurfaceResponse.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;


CommanderGetSurfaceResponse::CommanderGetSurfaceResponse() :
        imageFormat_(ImageFormat::Unknown), imageBuffer_() {}

void CommanderGetSurfaceResponse::set_image(CommanderGetSurfaceResponse::ImageFormat format,
                                            CommanderGetSurfaceResponse::ImageBuffer&& imageBuffer)
{
    imageFormat_ = format;
    imageBuffer_ = std::move(imageBuffer);
}

CommanderGetSurfaceResponse::ImageFormat CommanderGetSurfaceResponse::get_image_format() const
{
    return imageFormat_;
}

const CommanderGetSurfaceResponse::ImageBuffer& CommanderGetSurfaceResponse::get_image_buffer() const
{
    return imageBuffer_;
}

IParcel::SerializedParcel CommanderGetSurfaceResponse::serialize(AParcelSerializer& serializer)
{
    return serializer.serialize(*this);
}
