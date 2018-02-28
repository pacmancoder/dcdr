#include <gtest/gtest.h>

#include <dcdr/server/core/Surface.h>

using namespace Dcdr::Server;

class SurfaceTest : public ::testing::Test {};


TEST_F(SurfaceTest, SurfaceBufferInfoTest)
{
    Surface surface(24, 16, 8);
    auto buffer = surface.get_surface_buffer(SurfaceFormat::Rgb24Unsigned);
    ASSERT_TRUE(buffer.width == 24);
    ASSERT_TRUE(buffer.height == 16);
    ASSERT_TRUE(buffer.format == SurfaceFormat::Rgb24Unsigned);
    ASSERT_TRUE(buffer.data.size() == 24 * 16 * 3);
}

TEST_F(SurfaceTest, SurfaceBufferDataTest)
{
    Surface surface(2, 2, 1);
    surface.commit_chunk(
            Chunk(ChunkRect{0,1,1,1}, std::vector<ChunkPixel> {ChunkPixel {{1, 1, 1}, 1}}));

    auto buffer = surface.get_surface_buffer(SurfaceFormat::Rgb24Unsigned);

    std::vector<uint8_t> expectedBufferData = {0,0,0,  0,0,0,  255,255,255,  0,0,0};
    ASSERT_EQ(buffer.width, 2);
    ASSERT_EQ(buffer.height, 2);
    ASSERT_EQ(buffer.data, expectedBufferData);
}


TEST_F(SurfaceTest, SurfaceBufferMipmapDataTest)
{
    Surface surface(8, 8, 4);

    auto pixels = std::vector<ChunkPixel>(4 * 4);
    for (auto& pixel : pixels)
    {
        pixel.samples = 1;
        pixel.color = Dcdr::Types::Color(0.f);
    }
    // make test pattern
    pixels[0 ].color = Dcdr::Types::Color(1.f, 0.f, 0.f);
    pixels[2 ].color = Dcdr::Types::Color(1.f);
    pixels[8 ].color = Dcdr::Types::Color(1.f);
    pixels[10].color = Dcdr::Types::Color(1.f);

    surface.commit_chunk(Chunk(ChunkRect{0, 0, 4, 4}, pixels));
    pixels[0 ].color = Dcdr::Types::Color(0.f, 1.f, 0.f);
    surface.commit_chunk(Chunk(ChunkRect{4, 0, 4, 4}, pixels));
    pixels[0 ].color = Dcdr::Types::Color(0.f, 0.f, 1.f);
    surface.commit_chunk(Chunk(ChunkRect{0, 4, 4, 4}, pixels));
    pixels[0 ].color = Dcdr::Types::Color(1.f, 1.f, 0.f);
    surface.commit_chunk(Chunk(ChunkRect{4, 4, 4, 4}, pixels));

    auto buffer = surface.get_surface_buffer(SurfaceFormat::Rgb24Unsigned);

    std::vector<uint8_t> expectedFullBufer = {
              255,0,0,     0,0,0, 255,255,255, 0,0,0, 0,255,0,     0,0,0, 255,255,255, 0,0,0,
              0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0,
              255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0,
              0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0,
              0,0,255,     0,0,0, 255,255,255, 0,0,0, 255,255,0,   0,0,0, 255,255,255, 0,0,0,
              0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0,
              255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0,
              0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0, 0,0,0,       0,0,0};
    ASSERT_EQ(buffer.data, expectedFullBufer);

    // 1 level mipmap
    buffer = surface.get_surface_buffer(SurfaceFormat::Rgb24Unsigned, 1);

    std::vector<uint8_t> expectedMipmapLevel1 = {
            255,0,0,     255,255,255, 0,255,0,     255,255,255,
            255,255,255, 255,255,255, 255,255,255, 255,255,255,
            0,0,255,     255,255,255, 255,255,0,   255,255,255,
            255,255,255, 255,255,255, 255,255,255, 255,255,255};
    ASSERT_EQ(buffer.data, expectedMipmapLevel1);

    // 2 level mipmap
    buffer = surface.get_surface_buffer(SurfaceFormat::Rgb24Unsigned, 2);

    std::vector<uint8_t> expectedMipmapLevel2 = {
            255,0,0, 0,255,0,
            0,0,255, 255,255,0,};

    ASSERT_EQ(buffer.data, expectedMipmapLevel2);
}