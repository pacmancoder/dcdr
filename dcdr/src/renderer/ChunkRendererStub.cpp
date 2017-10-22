#include <dcdr/renderer/ChunkRendererStub.h>

#include <cstdlib>
#include <dcdr/Types.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

Types::Color ChunkRendererStub::render_sample(Types::Offset x, Types::Offset y)
{
    Types::Color result;
    result.r = Types::Real(y) / 480;
    result.g = Types::Real(x) / 640;
    result.b = 0.0;
    return result;
}
