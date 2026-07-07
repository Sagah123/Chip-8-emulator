#pragma once
#include <cstdint>
#include <string>
#include <random>
#include <array>

class Chip8 {
    public:
        static constexpr unsigned int VIDEO_WIDTH = 64;
        static constexpr unsigned int VIDEO_HEIGHT = 32;
        static constexpr unsigned int MEMORY_SIZE = 4096;
        static constexpr unsigned int START_ADDRESS = 0x200;
        static constexpr unsigned int FONTSET_START_ADDRESS = 0x50;
        static constexpr unsigned int FONTSET_SIZE = 80;
        std::array<uint8_t, 16> V{};
        std::array<uint8_t, MEMORY_SIZE> memory{};
        std::array<uint8_t, 16> keypad{};
        uint16_t I{};
        uint16_t pc = START_ADDRESS;
        std::array<std::array<bool,VIDEO_WIDTH>, VIDEO_HEIGHT> display{};
        std::array<uint16_t, 16> stack{};
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<uint8_t> distrib;
        uint8_t sp{};
        uint8_t delay_timer{};
        uint8_t sound_timer{};
        bool drawFlag = false;
        Chip8();
        bool loadROM(const std::string& filename);
        void emulateCycle();
};