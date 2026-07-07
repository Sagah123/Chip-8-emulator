#include "EmulatorState.h"
#include "AppEngine.h"
#include <fstream>
#include <iostream>

EmulatorState::EmulatorState(AppEngine* engine, const std::string& romPath)
    :platform("CHIP8 emulator created by sagah", 20)
{
    this->engine = engine;
    if (!chup8.loadROM(romPath)) {
        throw std::runtime_error("ROM-файл не найден по пути: " + romPath);
    }
    lastCycleTime = std::chrono::high_resolution_clock::now();
    lastTimerTime = std::chrono::high_resolution_clock::now();

}
EmulatorState::~EmulatorState(){}
void EmulatorState::handleInput() {
    bool quitRequested = platform.processInput(chup8.keypad);
    if (!quitRequested){
        engine->quit();
    }
}
void EmulatorState::update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<double, std::milli>(currentTime - lastCycleTime).count() > 2.0){
        chup8.emulateCycle();
        lastCycleTime = currentTime;
    }
    if (std::chrono::duration<double, std::milli>(currentTime - lastTimerTime).count() >= 16.6) {
        if (chup8.delay_timer > 0) chup8.delay_timer--;
        if (chup8.sound_timer > 0) chup8.sound_timer--;
        lastTimerTime = currentTime;
    }
}
void EmulatorState::render() {
    if (chup8.drawFlag){
        platform.update(chup8.display);
        chup8.drawFlag = false;
    }
}