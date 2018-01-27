#!/bin/bash
# flatc should be in path!
flatc --cpp dncp.fbs
mv dncp_generated.h ../../dcdr-interconnect/src/serialization/FlatBuffers.h
