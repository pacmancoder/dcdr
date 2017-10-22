#include <dcdr/renderer/ChunkRendererStub.h>

#include <cstdlib>
#include <dcdr/Types.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

Types::Color ChunkRendererStub::render_sample(Types::Offset x, Types::Offset y) {
    Types::Color result;
    result.r = Types::Real(std::rand()) / RAND_MAX;
    result.g = Types::Real(std::rand()) / RAND_MAX;
    result.b = Types::Real(std::rand()) / RAND_MAX;
}
