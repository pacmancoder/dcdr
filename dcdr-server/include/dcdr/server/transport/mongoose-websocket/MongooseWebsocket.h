#pragma once

#include <memory>

#include <dcdr/server/transport/ITransport.h>

namespace Dcdr::Interconnect
{
    class IParcelSerializer;
    class IParcelDeserializer;
}

namespace Dcdr::Server
{
    class Core;

    class MongooseWebsocket : public ITransport
    {
    public:
        struct MongooseWebsocketImpl;

    public:
        using ParcelSerizlizerPtr = std::shared_ptr<Interconnect::IParcelSerializer>;
        using ParcelDeserializerPtr = std::shared_ptr<Interconnect::IParcelDeserializer>;
        using CorePtr = std::shared_ptr<Core>;

    public:
        MongooseWebsocket(
                const CorePtr& core,
                const ParcelSerizlizerPtr& serizlizer,
                const ParcelDeserializerPtr& deserizlizer);

        void open() override;

        void close() override;

        virtual ~MongooseWebsocket();
    private:
        std::unique_ptr<MongooseWebsocketImpl> impl_;
    };
}