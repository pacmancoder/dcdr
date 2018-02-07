#include <gtest/gtest.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersCommanderRequestSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/worker/AWorkerRequestParcel.h>
#include <dcdr/messaging/worker/WorkerConnectRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceResponse.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoResponse.h>

using namespace Dcdr::Interconnect;

class FlatBuffersInterconnectTest : public ::testing::Test
{
protected:
    FlatBuffersParcelSerializer serializer_;
    FlatBuffersParcelDeserializer deserializer_;
};

TEST_F(FlatBuffersInterconnectTest, WorkerConnectRequestTest)
{
    const AWorkerRequestParcel::SessionID session {0, 1, 2, 3, 4, 6, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const WorkerConnectRequest::Token     token   {0, 1, 2, 3, 4, 6, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    WorkerConnectRequest request;
    request.set_session_id(session);
    request.set_token(token);

    auto serializedParcel = request.serialize(serializer_);
    auto deserializedParcel = deserializer_.deserialize(serializedParcel);

    auto deserializedRequest = dynamic_cast<WorkerConnectRequest*>(deserializedParcel.get());

    ASSERT_TRUE(deserializedRequest->get_session_id() == session);
    ASSERT_TRUE(deserializedRequest->get_token()      == token);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSurfaceInfoRequestTest)
{
    CommanderGetSurfaceInfoRequest request;

    auto serializedParcel = request.serialize(serializer_);
    auto deserializedParcel = deserializer_.deserialize(serializedParcel);

    auto deserializedRequest = dynamic_cast<CommanderGetSurfaceInfoRequest*>(deserializedParcel.get());
    ASSERT_TRUE(deserializedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSurfaceRequestTest)
{
    CommanderGetSurfaceRequest request;

    auto serializedParcel = request.serialize(serializer_);
    auto deserializedParcel = deserializer_.deserialize(serializedParcel);

    auto deserializedRequest = dynamic_cast<CommanderGetSurfaceRequest*>(deserializedParcel.get());
    ASSERT_TRUE(deserializedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSurfaceInfoResponseTest)
{
    CommanderGetSurfaceInfoResponse response;
    response.set_width(1920);
    response.set_height(1080);

    auto serializedParcel = response.serialize(serializer_);
    auto deserializedParcel = deserializer_.deserialize(serializedParcel);

    auto deserializedResponse = dynamic_cast<CommanderGetSurfaceInfoResponse*>(deserializedParcel.get());
    ASSERT_TRUE(deserializedResponse != nullptr);

    ASSERT_TRUE(deserializedResponse->get_width()  == 1920);
    ASSERT_TRUE(deserializedResponse->get_height() == 1080);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSurfaceResponseTest)
{
    const CommanderGetSurfaceResponse::ImageFormat imageFormat(CommanderGetSurfaceResponse::ImageFormat::Png);
    const CommanderGetSurfaceResponse::ImageBuffer imageBuffer {1, 2, 3, 4};

    CommanderGetSurfaceResponse response;
    response.set_image(imageFormat, std::vector<uint8_t>(imageBuffer));

    auto serializedParcel = response.serialize(serializer_);
    auto deserializedParcel = deserializer_.deserialize(serializedParcel);

    auto deserializedResponse = dynamic_cast<CommanderGetSurfaceResponse*>(deserializedParcel.get());
    ASSERT_TRUE(deserializedResponse != nullptr);

    ASSERT_TRUE(deserializedResponse->get_image_format() == imageFormat);
    ASSERT_EQ(deserializedResponse->get_image_buffer(), imageBuffer);
}