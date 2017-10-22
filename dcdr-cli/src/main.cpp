#include <iostream>
#include <dcdr/Types.h>
#include <dcdr/renderer/Surface.h>
#include <dcdr/renderer/ChunkExchangeNodeStub.h>
#include <dcdr/renderer/ChunkRendererStub.h>
#include <dcdr/renderer/ISurfaceRasterizer.h>

#include <vector>
#include <string>
#include <fstream>
#include <memory>

using namespace Dcdr;
using namespace Dcdr::Renderer;


class PpmRasterizer : public ISurfaceRasterizer
{
public:
    PpmRasterizer(Types::Offset width, Types::Offset height) :
            width_(width),
            height_(height),
            pixels_(width * height) {}

    void set_image_size(Types::Size width, Types::Size height) override
    {
        // ignore for now
    }

    void draw_pixel(Types::Vec3 color, Types::Offset x, Types::Offset y) override
    {
        pixels_[y * width_ + x][0] = (unsigned char)(color.r * 255);
        pixels_[y * width_ + x][1] = (unsigned char)(color.g * 255);
        pixels_[y * width_ + x][2] = (unsigned char)(color.b * 255);
    }

    void save_file(const std::string& filename)
    {
        std::ofstream file(filename, std::ofstream::binary);

        file << "P3" << std::endl;
        file << width_ << " " << height_ << std::endl;
        file << "255" << std::endl;

        for (auto& pixel : pixels_)
            file << Types::Offset(pixel[0]) << " " << Types::Offset(pixel[1]) << " " << Types::Offset(pixel[2])
                 << std::endl;
    }

private:
    Types::Offset width_;
    Types::Offset height_;

    std::vector<unsigned char[3]> pixels_;
};

int main(int argc, char* argv[])
{
    const Types::Size SURFACE_WIDTH = 640;
    const Types::Size SURFACE_HEIGHT = 480;
    const Types::Size CHUNK_SIZE = 16;

    ChunkExchangeNodeStub exchangeNode;
    ChunkRendererStub renderer;


    Surface surface(SURFACE_WIDTH, SURFACE_HEIGHT, CHUNK_SIZE, exchangeNode);

    std::shared_ptr < PpmRasterizer > rasterizer
            = std::shared_ptr < PpmRasterizer > (new PpmRasterizer(SURFACE_WIDTH, SURFACE_HEIGHT));

    surface.set_rasterizer(rasterizer);
    for (int i = 0; i < 1024 * 16; ++i)
        surface.render_single_chunk(renderer);

    rasterizer->save_file("test.ppm");

    return 0;
}