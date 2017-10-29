#include <iostream>
#include <dcdr/Types.h>
#include <dcdr/renderer/Surface.h>
#include <dcdr/pathtracing/PathTracer.h>

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <dcdr/scene/Scene.h>
#include <dcdr/scene/Camera.h>
#include <dcdr/scene/objects/Sphere.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;


namespace
{
    class PpmRasterizer : public ISurfaceRasterizer
    {
    public:
        PpmRasterizer(Types::Offset width, Types::Offset height) :
                width_(width),
                height_(height),
                pixels_(width * height)
        {}

        void set_image_size(Types::Size width, Types::Size height) override
        {
            // ignore for now
        }

        void draw_pixel(Types::Vec3 color, Types::Offset x, Types::Offset y) override
        {
            if (color.r > 1.0) color.r = 0.99; if (color.r < 0.0) color.r = 0.0;
            if (color.g > 1.0) color.g = 0.99; if (color.g < 0.0) color.g = 0.0;
            if (color.b > 1.0) color.b = 0.99; if (color.b < 0.0) color.b = 0.0;

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

    class ChunkExchangeNodeStub : public IChunkExchangeNode
    {
    public:
        ChunkSeizureStatus seizure_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override
        {
            return ChunkSeizureStatus::Success;
        }

        ChunkReleaseStatus release_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override
        {
            return ChunkReleaseStatus::Success;
        }

        void save_chunk(const Chunk& chunk, Dcdr::Types::Offset x, Dcdr::Types::Offset y) override
        {

        }

        Chunk request_chunk(Dcdr::Types::Offset x, Dcdr::Types::Offset y) override
        {
            return Chunk(x, y, 1, 1);
        }
    };
}
int main(int argc, char* argv[])
{
    const Types::Size SURFACE_WIDTH = 800;
    const Types::Size SURFACE_HEIGHT = 640;
    const Types::Size CHUNK_SIZE = 16;

    ChunkExchangeNodeStub exchangeNode;

    Scene::ScenePtr scene = Scene::ScenePtr(new Scene::Scene());

    Scene::CameraUniquePtr camera = std::make_unique<Scene::Camera>(
            Types::Vec3(0, 0, 0), // position
            Types::Vec3(0, 0, 1), // eye
            Types::Vec3(0, 1, 0), // up
            55, // fov
            Types::Vec3(0, 0, -4), // focal point
            0.10); // aperture radius;
    scene->set_camera(std::move(camera));

    auto sphere1 = std::make_unique<Scene::Sphere>(Types::Vec3(0, 0, Types::Real(-4.0)), Types::Real(0.5), 0);
    auto sphere2 = std::make_unique<Scene::Sphere>(Types::Vec3(2, 3, Types::Real(-6.0)), Types::Real(0.5), 0);
    scene->add_object("Sphere1", std::move(sphere1));
    scene->add_object("Sphere2", std::move(sphere2));

    PathTracing::PathTracer renderer(scene);

    Surface surface(SURFACE_WIDTH, SURFACE_HEIGHT, CHUNK_SIZE, exchangeNode);


    std::shared_ptr < PpmRasterizer > rasterizer
            = std::shared_ptr < PpmRasterizer > (new PpmRasterizer(SURFACE_WIDTH, SURFACE_HEIGHT));

    surface.set_rasterizer(rasterizer);
    for (int i = 0; i < 1024 * 4; ++i)
        surface.render_single_chunk(renderer);

    rasterizer->save_file("test.ppm");

    return 0;
}