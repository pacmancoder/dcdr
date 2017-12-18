#!/bin/bash
# flatc should be in path!
flatc --cpp dcdr_flatbuffers.fbs
mv dcdr_flatbuffers_generated.h ../../src/serialization/FlatBuffers.h
