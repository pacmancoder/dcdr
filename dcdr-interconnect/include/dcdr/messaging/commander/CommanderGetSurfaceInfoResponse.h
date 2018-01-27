#pragma once

#include <dcdr/messaging/commander/ACommanderResponseParcel.h>

namespace Dcdr::Interconnect
{
    class CommanderGetSurfaceInfoResponse : public ACommanderResponseParcel
    {
    public:
        CommanderGetSurfaceInfoResponse() = default;

        void set_width(uint32_t width);
        void set_height(uint32_t height);

        uint32_t get_width() const;
        uint32_t get_height() const;

    public:
        SerializedParcel serialize(AParcelSerializer& serializer) override;

    private:
        uint32_t width_;
        uint32_t height_;
    };
}