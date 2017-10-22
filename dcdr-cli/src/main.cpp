#include <iostream>
#include <dcdr/Types.h>
#include <dcdr/renderer/Surface.h>
#include <dcdr/renderer/ChunkExchangeNodeStub.h>
#include <dcdr/renderer/ChunkRendererStub.h>
#include <dcdr/renderer/ISurfaceRasterizer.h>

#include <SDL2/SDL.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;


class Rasterizer : ISurfaceRasterizer
{
    void set_image_size(Types::Size width, Types::Size height) override
    {
        // nothing
    }

    void draw_pixel(Types::Vec3 color, Types::Offset x, Types::Offset y) override
    {

    }
};

int main(int argc, char* argv[])
{
    const Types::Size SURFACE_WIDTH = 640;
    const Types::Size SURFACE_HEIGHT = 480;
    const Types::Size CHUNK_SIZE = 16;

    ChunkExchangeNodeStub exchangeNode;
    ChunkRendererStub renderer;



    Surface surface(SURFACE_WIDTH, SURFACE_HEIGHT, CHUNK_SIZE, exchangeNode);



    SDL_Event sdl_event;
    SDL_Renderer *sdl_renderer;
    SDL_Window *sdl_window;
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SURFACE_WIDTH, SURFACE_HEIGHT, 0, &sdl_window, &sdl_renderer);
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
    SDL_RenderClear(sdl_renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    /*for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }*/
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
    
    return 0;
}