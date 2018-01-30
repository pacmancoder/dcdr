DCDR
===
### Distributed Computing Distributed Ray Tracer
[![Build Status](https://travis-ci.org/pacmancoder/dcdr.svg?branch=master)](https://travis-ci.org/pacmancoder/dcdr)

#### Important
This project was started as a project for my bachelor thesis and it does not pretend to be a feature-full industry-grade renderer.  
I plan to prepare the first stable version until June, 2018. Until then the project will be developed only by myself.

#### Goals
- Distributed Ray Tracer (Path Tracer)
- All computations can be distributed over network on heterogeneous.
- Current progress and computation network info can be viewed in real-time.

#### Current Status
Currently I am working on the implementation of connectivity between DCDR-Server, DCDR-Worker-s and DCDR-WebUI.

#### Technology stack

##### Languages
- C ++ 17 for both DCDR-Server and DCDR-Worker modules
- JS for WebUI operations

##### Protocols
- WebSocket for DCDR-Server <\ -> DCDR-WebUI communications
- TCP sockets for DCDR-Server <\ -> DCDR-Worcel communications

##### Build / Deploy / CI
- CMake as main C ++ build system
- Travis CI as continuous integration platform

##### Libraries
- [Mongoose](https://github.com/cesanta/mongoose) as embedded web-server
- [FlatBuffers](https://github.com/google/flatbuffers) for Dcdr-Interconnect protcols are on with network transmission
- [Google Test](https://github.com/google/googletest) as main C ++ testing framework
- [LodePNG](https://github.com/lvandeve/lodepng) for rendered image encoding / scene textures decoding
- [microtar](https://github.com/rxi/microtar) as container for scene format
- [SQLite](https://www.sqlite.org/) as scene info data storage
