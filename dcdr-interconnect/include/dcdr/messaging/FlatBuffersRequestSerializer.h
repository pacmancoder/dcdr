#pragma once

#include <dcdr/messaging/IRequestSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{

    class FlatBuffersRequestSerializer : public IRequestSerializer
    {

    public:
        void set_request(IRequestPtr request) override;

        void set_connection(const std::string& connection) override;

        std::vector<uint8_t> serialize() override;

    protected:
        std::vector<uint8_t> serialize(const ConnectRequest &request) override;

    private:
        IRequestPtr request_;
        std::string connection_;
    };
}