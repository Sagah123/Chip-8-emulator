#include <string>
#include <iostream>
#include "AppEngine.h"
#include "EmulatorState.h"
#include "filesystem"

int main(int argc, char* argv[]) {
     int i = 1;
        std::filesystem::directory_iterator roms = std::filesystem::directory_iterator("roms");
        std::vector<std::filesystem::path> romList;
        for(const auto& rom: roms){
            romList.push_back(rom.path());
            i++;
        }
    while(true){
        std::cout << "========== CHIP-8 EMULATOR ==========\n";
        std::cout << "Enter ROM corresponding number (e.g. 15 for Tetris): " << std::endl;
        for (size_t idx = 0; idx < romList.size(); ++idx) {
            std::cout << idx + 1 << ": " << romList[idx].stem().string() << std::endl;
        }
        std::cout << "0: Exit" << std::endl;
        int romNum;
        std::cin >> romNum;
        if (romNum == 0){
            break;
        }
        if (romNum < 1 || romNum > romList.size()) {
            std::cout << "Invalid number. Try again.\n\n";
            continue; 
        }
        std::string fullPath = romList[romNum-1].string();
        AppEngine engine;
        try {
            AppState* game = new EmulatorState(&engine, fullPath);
            engine.changeState(game);
            engine.run();   
        } 
        catch (const std::exception& e) {
            std::cerr << "\n Critical Error " << e.what() << std::endl;
            return 1;
        }
        std::cout << "\nReturned to main menu.\n\n";
    }
    std::cout << "Emulator shut down correctly\n";
    return 0;
}
