#include "EmulatorState.h"
#include <iostream>

EmulatorState::EmulatorState(const std::string& romPath)
    :platform("CHIP8 emulator created by sagah", 20)
{
    chup8.loadROM(romPath);
    lastCycleTime = std::chrono::high_resolution_clock::now();
    lastTimerTime = std::chrono::high_resolution_clock::now();
}
void EmulatorState::handleInput() {
    platform.processInput(chup8.keypad);
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