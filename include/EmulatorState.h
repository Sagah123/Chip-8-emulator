#include <string>
#include "Platform.h"
#include "Chip8.h"
#include "AppEngine.h"
#include "AppState.h"
#pragma once
#include <chrono>


class EmulatorState: public AppState{
    public:
        EmulatorState(AppEngine* engine, const std::string& romPath);
        ~EmulatorState() override;
        void render() override;
        void handleInput() override;
        void update() override;
    private:
        AppEngine* engine;
        Platform platform;
        Chip8 chup8;
        std::chrono::high_resolution_clock::time_point lastCycleTime;
        std::chrono::high_resolution_clock::time_point lastTimerTime;
            
};