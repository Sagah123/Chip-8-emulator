#include "Chip8.h"
#include <iostream>
#include "Platform.h"
#include "EmulatorState.h"
#include <chrono>
#include <thread>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    try {
        std::string romPath = "";
        if (argc >= 2) {
            romPath = argv[1];
        } else{
            std::cout << "========== CHIP-8 EMULATOR ==========\n";
            std::cout << "Available ROMs in 'roms' folder:\n";
            std::vector<std::string> romFiles;
            int ind = 1;
            if (fs::exists("roms") && fs::is_directory("roms")){
                for (const auto& enter: fs::directory_iterator("roms")){
                    std::cout << "[" << ind << "] " << enter.path().filename().string() << "\n";
                    romFiles.push_back(enter.path().string());
                    ind++;
                }
            } else {
                std::cerr << "CRITICAL: Folder 'roms' not found next to the executable!\n";
                return -1;
            } if (romFiles.empty()){
                std::cout << "No ROMs found in the directory";
                return -1;
            }
            std::cout << "-------------------------------------\n";
            std::cout << "Enter game number to play: ";
            int choice = 0;
            std::cin >> choice;
            if (choice > 0 && choice <= romFiles.size()){
                romPath = romFiles[choice - 1];
            } else {
                std::cerr << "Invalid choice. Exiting.\n";
                return -1;
            }
        } 
        EmulatorState emulator(romPath);
        while(true) {
            emulator.handleInput();
            emulator.update();
            emulator.render();
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}