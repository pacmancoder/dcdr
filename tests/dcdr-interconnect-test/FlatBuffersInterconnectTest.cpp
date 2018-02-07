#include <gtest/gtest.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/commander/CommanderRequestParcels.h>

using namespace Dcdr::Interconnect;

class FlatBuffersInterconnectTest : public ::testing::Test
{
protected:
    FlatBuffersParcelSerializer serializer_;
    FlatBuffersParcelDeserializer deserializer_;
};


TEST_F(FlatBuffersInterconnectTest, CommanderGetJobListRequestParcelTest)
{
    CommanderGetJobListRequestParcel request;

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobListRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobInfoRequestParcelTest)
{
    CommanderGetJobInfoRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobPreviewRequestParcel)
{
    CommanderGetJobPreviewRequestParcel request(42, 2);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobPreviewRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_mipmap_level() == 2);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobArtifactRequestParcel)
{
    CommanderGetJobArtifactRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobArtifactRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
}

TEST_F(FlatBuffersInterconnectTest, CommanderSetJobStateRequestParcel)
{
    CommanderSetJobStateRequestParcel request(42, Commander::JobState::InProgress);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderSetJobStateRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_job_state() == Commander::JobState::InProgress);
}

TEST_F(FlatBuffersInterconnectTest, CommanderAddJobRequestParcel)
{
    CommanderAddJobRequestParcel request(42, 2.0f);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderAddJobRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_scene_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_scale() == 2.0f);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSceneListRequestParcel)
{
    CommanderGetSceneListRequestParcel request;

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetSceneListRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetNodeListRequestParcel)
{
    CommanderGetNodeListRequestParcel request;

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetNodeListRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetNodeInfoRequestParcel)
{
    CommanderGetNodeInfoRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetNodeInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_node_id() == 42);
}

TEST_F(FlatBuffersInterconnectTest, CommanderSetNodeStateRequestParcel)
{
    CommanderSetNodeStateRequestParcel request(42, Commander::NodeState::Malfunctioned);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderSetNodeStateRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_node_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_node_state() == Commander::NodeState::Malfunctioned);
}