#include <cstdint>
#include <string>
#include <random>
#include <array>


class Chip8 {
    public:
        std::array<uint8_t, 16> V{};
        std::array<uint8_t, 4096> memory{};
        uint16_t I{};
        uint16_t pc = 0x200;
        std::array<std::array<bool,64>, 32> display{};
        std::array<uint16_t, 16> stack{};
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<uint8_t> distrib;
        uint8_t sp{};
        uint8_t delay_timer{};
        uint8_t sound_timer{};
        Chip8();
        bool loadROM(const std::string& filename);
        void emulateCycle();
};