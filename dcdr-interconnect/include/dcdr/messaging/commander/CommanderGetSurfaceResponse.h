#pragma once

#include <dcdr/messaging/commander/ACommanderResponseParcel.h>

namespace Dcdr::Interconnect
{
    class CommanderGetSurfaceResponse : public ACommanderResponseParcel
    {
    public:
        using ImageBuffer = std::vector<uint8_t>;

        enum class ImageFormat : uint16_t
        {
            Unknown,
            Png,
        };

    public:
        CommanderGetSurfaceResponse();

        void set_image(ImageFormat format, ImageBuffer&& imageBuffer);

        ImageFormat get_image_format() const;
        const ImageBuffer& get_image_buffer() const;

    public:
        SerializedParcel serialize(AParcelSerializer& serializer) override;

    private:
        ImageFormat imageFormat_;
        ImageBuffer imageBuffer_;
    };
}