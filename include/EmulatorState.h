#include <string>
#include "Platform.h"
#include "Chip8.h"
#include "AppState.h"
#pragma once
#include <chrono>


class EmulatorState: public AppState{
    public:
        EmulatorState(const std::string& romPath);
        void render() override;
        void handleInput() override;
        void update() override;
    private:
        Platform platform;
        Chip8 chup8;
        std::chrono::high_resolution_clock::time_point lastCycleTime;
        std::chrono::high_resolution_clock::time_point lastTimerTime;
            
};