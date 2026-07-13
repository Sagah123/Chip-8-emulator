# 👾 CHIP-8 Emulator

![C++](https://img.shields.io/badge/C++-20-blue.svg?style=for-the-badge&logo=c%2B%2B)
![SDL3](https://img.shields.io/badge/SDL-3.4.8-orange.svg?style=for-the-badge&logo=sdl)
![CMake](https://img.shields.io/badge/CMake-3.20+-green.svg?style=for-the-badge&logo=cmake)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg?style=for-the-badge)

A cross-platform CHIP-8 emulator written in C++20.

I built this to actually understand what happens under the hood of a CPU — memory layout, opcode decoding, timing — instead of just reading about it.

The hard parts: syncing a 500Hz CPU loop against a 60Hz timer, decoding 16-bit opcodes into the right instructions, and getting sprite rendering to match the original XOR-based collision behavior.

Runs classic ROMs like Space Invaders, Tetris, and Pong, as well as newer homebrew titles like Astro Dodge.

---

## 🛠️ Getting Started

Thanks to CMake Presets, the project builds with just a couple of commands—no manual library installations required.

### Prerequisites
* A C++20 compatible compiler (MSVC, GCC/MinGW, or Clang)
* CMake 3.20 or newer
* Git
### Build Instructions (Terminal / PowerShell)

```bash
# 1. Clone the repository
git clone https://github.com/Sagah123/Chip-8-emulator.git
cd Chip-8-emulator

# 2. Configure the project (SDL3 will be fetched automatically)
# For Windows:
cmake --preset windows-default
# For Linux (Ninja / Makefiles):
cmake --preset ninja-default

# 3. Build the project
cmake --build build

# 4. Run the emulator
./build/Chip8
```
---

## 📂 Project Structure

Here is the exact layout of the repository, separating the core hardware logic, the state engine, and the platform-specific rendering subsystems:

```text
Chip-8-emulator/
├── CMakeLists.txt        # Build configuration
├── CMakePresets.json     # Presets for cross-platform builds
├── include/              # Header files
│   ├── Chip8.h           # Core CPU registers, memory map, and fontset definitions
│   ├── AppEngine.h       # Main application controller and abstract AppState interface
│   ├── Platform.h        # SDL3 hardware abstraction layer (Video & Input wrappers)
│   └── EmulatorState.h   # Concrete app state driving the microsecond-accurate loop
├── src/                  # Source files
│   ├── main.cpp          # Entry point and terminal-based ROM selection menu
│   ├── Chip8.cpp         # Opcode fetch-decode-execute matrix and bitwise logic
│   ├── AppEngine.cpp     # Game loop runner and dynamic state switcher
│   ├── Platform.cpp      # SDL3 window creation, texture streaming, and keyboard polling
│   └── EmulatorState.cpp # Chrono-based throttling for 500Hz CPU / 60Hz Timer sync
└── roms/                 # Directory containing CHIP-8 game files
```
---

## 📸 Gallery

> **Note:** Screenshots of the emulator running various ROMs.
> 
> <details>
> <summary>Click to expand screenshots</summary>
> 
> | Space Invaders | Pong2 | Astro Dodge | Sqrt | IBM's logo |
> |:---:|:---:|:---:|:---:|:---:|
> | <img src="https://github.com/user-attachments/assets/46c88293-b485-448b-9623-03f9fe787c78" width="180"/><br><img src="https://github.com/user-attachments/assets/d959f823-36bd-4e16-b7f2-38e99c5df789" width="180"/><br><img src="https://github.com/user-attachments/assets/53234e74-efe3-41b6-8e35-916c67dd02cd" width="180"/> | <img src="https://github.com/user-attachments/assets/a2bbaf32-0254-4568-be44-7c17fd098c2b" width="180"/><br><img src="https://github.com/user-attachments/assets/ad8c1e7a-13b8-461e-9a24-c53f62de700c" width="180"/> | <img src="https://github.com/user-attachments/assets/c5abb0cd-e2c4-4a8f-bf9c-00efacec07e0" width="180"/><br><img src="https://github.com/user-attachments/assets/66202390-9b4a-4655-8435-829e221d383f" width="180"/><br><img src="https://github.com/user-attachments/assets/929dd440-20d0-48ee-830e-960c4ffa28ee" width="180"/> | <img src="https://github.com/user-attachments/assets/51f18dd6-a72f-4b4f-89f6-7c50bbe4bbd6" width="180"/> | <img src="https://github.com/user-attachments/assets/d3c42cd7-c166-49b8-a36f-c8a872550763" width="180"/> |
> 
> </details>


