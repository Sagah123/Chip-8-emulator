#include "Platform.h"
#include <iostream>
#include <unordered_map>

static const std::unordered_map<SDL_Keycode, uint8_t> keyMap = {
    {SDLK_1, 0x1}, {SDLK_2, 0x2}, {SDLK_3, 0x3}, {SDLK_4, 0xC},
    {SDLK_Q, 0x4}, {SDLK_W, 0x5}, {SDLK_E, 0x6}, {SDLK_R, 0xD},
    {SDLK_A, 0x7}, {SDLK_S, 0x8}, {SDLK_D, 0x9}, {SDLK_F, 0xE},
    {SDLK_Z, 0xA}, {SDLK_X, 0x0}, {SDLK_C, 0xB}, {SDLK_V, 0xF}
};

Platform::Platform(const char* title, int scale, int width, int height)
: window(nullptr, &SDL_DestroyWindow), 
  renderer(nullptr, &SDL_DestroyRenderer), 
  texture(nullptr, &SDL_DestroyTexture)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Error at initialize SDL" << SDL_GetError() << "\n";
        throw std::runtime_error("SDL initialization failed");
    }
    SDL_Window* raw_window = nullptr;
    SDL_Renderer* raw_renderer = nullptr;
    
    if (SDL_CreateWindowAndRenderer(title, 64 * scale, 32 * scale, 0, &raw_window, &raw_renderer) < 0){
        std::cout << "Error at creating window/renderer: " << SDL_GetError() << "\n";
        throw std::runtime_error("Window creation failed");
    }
    window.reset(raw_window);
    renderer.reset(raw_renderer);
    SDL_Texture* raw_texture = SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!raw_texture){
        std::cout << "Error at creating texture: " << SDL_GetError() << "\n";
        throw std::runtime_error("Texture creation failed");
    }
    texture.reset(raw_texture);
    SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
}

bool Platform::processInput(std::array<uint8_t, 16>& keypad){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_EVENT_QUIT) return false;
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) return false;
        if(event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP){
            auto iter = keyMap.find(event.key.key);
            if (iter != keyMap.end()){
                uint8_t state = (event.type == SDL_EVENT_KEY_DOWN) ? 1 : 0;
                keypad[iter->second] = state;
            }
        }
    }
    return true;
};

void Platform::update(const std::array<std::array<bool, 64>, 32>& display){
    std::array<uint32_t, 2048> pixelBuffer;
    for (auto y = 0; y < 32; y++ ){
        for (auto x = 0; x < 64; x++){
            pixelBuffer[y * 64 + x] = display[y][x] ? 0xFFFFFFFF : 0x000000FF;
        }
    }
    SDL_UpdateTexture(texture.get(), nullptr, pixelBuffer.data(), 64 * sizeof(uint32_t));
    SDL_RenderClear(renderer.get());
    SDL_RenderTexture(renderer.get(), texture.get(),nullptr, nullptr);
    SDL_RenderPresent(renderer.get());
}