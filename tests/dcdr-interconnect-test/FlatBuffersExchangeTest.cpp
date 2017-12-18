#include <gtest/gtest.h>
#include <dcdr/messaging/FlatBuffersRequestSerializer.h>
#include <dcdr/messaging/FlatBuffersRequestDeserializer.h>
#include <dcdr/messaging/ConnectRequest.h>

using namespace Dcdr::Interconnect;

class FlatBuffersExchangeTest : public ::testing::Test {};

TEST_F(FlatBuffersExchangeTest, RequestTest)
{
    FlatBuffersRequestSerializer serializer;
    serializer.set_request(std::make_unique<ConnectRequest>("test_token"));
    serializer.set_connection("test");

    auto buffer = serializer.serialize();

    FlatBuffersRequestDeserializer deserializer;
    deserializer.deserialize(buffer);

    auto deserializedRequest = deserializer.get_request();

    ASSERT_TRUE(dynamic_cast<ConnectRequest*>(deserializedRequest.get())->get_user_token() == "test_token");
}