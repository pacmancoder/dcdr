#pragma once

#include <dcdr/messaging/IRequestDeserializer.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ServerConnectionResolver;

    class FlatBuffersRequestDeserializer : public IRequestDeserializer
    {
    public:
        void deserialize(const std::vector<uint8_t> &buffer) override;

        IRequestPtr get_request() override;
        std::string get_connection() override;

    private:
        IRequestPtr request_;
        std::string connection_;
    };
}