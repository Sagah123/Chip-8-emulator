#pragma once
#include <cstdint>
#include <memory>
#include <array>
#include <SDL3/SDL.h>

class Platform{
    public:
        Platform(const char* title, int scale, int width = 64, int height = 32);
        void update(const std::array<std::array<bool,64>, 32>& display);
        bool processInput(std::array<uint8_t, 16>& keypad);
    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;

};