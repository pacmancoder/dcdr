#include <gtest/gtest.h>

#include <dcdr/server/core/Chunk.h>

using namespace Dcdr::Server;

class ChunkTest : public ::testing::Test {};

TEST_F(ChunkTest, NewChunkTest)
{
    ChunkRect bounds { 16, 0, 8, 8 };
    const std::vector<ChunkPixel> pixels(bounds.w * bounds.h);

    Chunk chunk(bounds);
    ASSERT_EQ(chunk.get_bounds().x, bounds.x);
    ASSERT_EQ(chunk.get_bounds().y, bounds.y);
    ASSERT_EQ(chunk.get_bounds().w, bounds.w);
    ASSERT_EQ(chunk.get_bounds().h, bounds.h);
    ASSERT_EQ(chunk.get_min_samples(), 0u);
    ASSERT_EQ(chunk.get_max_samples(), 0u);
    ASSERT_EQ(chunk.get_pixels(), pixels);
}

TEST_F(ChunkTest, ConstructFromBufferTest)
{
    const ChunkRect bounds { 16, 0, 8, 8 };

    const uint32_t START_SAMPLES = 42u;
    const uint32_t MIN_SAMPLES = 42u;
    const uint32_t MAX_SAMPLES = START_SAMPLES + bounds.w * bounds.h - 1u;

    std::vector<ChunkPixel> pixels(bounds.w * bounds.h);
    for (size_t y = 0; y < bounds.h; ++y)
    {
        for (size_t x = 0; x < bounds.w; ++x)
        {
            pixels[y * bounds.w + x].color.r = Dcdr::Types::Real(x);
            pixels[y * bounds.w + x].color.g = Dcdr::Types::Real(y);
            pixels[y * bounds.w + x].color.b = 255.0f - Dcdr::Types::Real(x);
            if (x == 1u && y == 0u)
            {
                pixels[y * bounds.w + x].samples =
                        static_cast<uint32_t>(MIN_SAMPLES);
            }
            else
            {
                pixels[y * bounds.w + x].samples =
                        static_cast<uint32_t>(START_SAMPLES + y * bounds.w + x);
            }

        }
    }

    Chunk chunk(bounds, pixels);
    ASSERT_EQ(chunk.get_min_samples(), MIN_SAMPLES);
    ASSERT_EQ(chunk.get_max_samples(), MAX_SAMPLES);
}

TEST_F(ChunkTest, AccumulateTest)
{
    ChunkRect bounds {0, 0, 2, 2};

    std::vector<ChunkPixel> chunkData1 = {
            {{0, 0, 0}, 0},
            {{4, 8,16}, 1},
            {{2, 4, 8}, 6},
            {{1, 2, 4}, 1}
    };

    std::vector<ChunkPixel> chunkData2 = {
            {{1, 2, 4}, 1},
            {{2, 4, 8}, 1},
            {{2, 8,16}, 2},
            {{1, 2, 4}, 1}
    };

    std::vector<ChunkPixel> chunkDataExpected = {
            {{1, 2, 4}, 1},
            {{3, 6,12}, 2},
            {{2, 4 + (4 * 2) / 8.0f, 8 + (8 * 2) / 8.0f}, 8},
            {{1, 2, 4}, 2}
    };

    Chunk chunk1(bounds, chunkData1);
    Chunk chunk2(bounds, chunkData2);
    chunk2.accumulate(chunk1);
    ASSERT_EQ(chunk2.get_pixels(), chunkDataExpected);
}