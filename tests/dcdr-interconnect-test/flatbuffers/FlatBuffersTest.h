#pragma once

#include <gtest/gtest.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

class FlatBuffersInterconnectTest : public ::testing::Test
{
protected:
    Dcdr::Interconnect::FlatBuffersParcelSerializer serializer_;
    Dcdr::Interconnect::FlatBuffersParcelDeserializer deserializer_;
};