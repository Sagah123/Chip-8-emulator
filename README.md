# 👾 CHIP-8 Emulator

![C++](https://img.shields.io/badge/C++-20-blue.svg?style=for-the-badge&logo=c%2B%2B)
![SDL3](https://img.shields.io/badge/SDL-3.4.8-orange.svg?style=for-the-badge&logo=sdl)
![CMake](https://img.shields.io/badge/CMake-3.20+-green.svg?style=for-the-badge&logo=cmake)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg?style=for-the-badge)

A highly accurate, cross-platform CHIP-8 emulator written in modern **C++20**. 

This project was developed to gain a deep understanding of CPU architecture, low-level memory management, and bitwise operations. The emulator supports classic ROMs (Space Invaders, Tetris, Pong, Life) and ensures an accurate reproduction of the original 1970s hardware logic.

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
git clone [https://github.com/Sagah123/Chip-8-emulator.git](https://github.com/Sagah123/Chip-8-emulator.git)
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
> | Space Invaders | Tetris | Game of Life |
> |:---:|:---:|:---:|
> | <img src="URL_TO_IMAGE_1" width="250"/> | <img src="URL_TO_IMAGE_2" width="250"/> | <img src="URL_TO_IMAGE_3" width="250"/> |
> 
> </details>

---

## 🧠 Technical Showcase

This repository demonstrates proficiency in the following technologies and concepts:
1. **Low-Level C++:** Extensive use of `uint8_t`, `uint16_t`, `size_t`, raw memory arrays, and pointers.
2. **Bitwise Arithmetic:** Decoding 16-bit opcodes (Fetch, Decode, Execute cycle), applying bitmasks, and utilizing bitwise shifts (`&`, `|`, `^`, `<<`, `>>`).
3. **Cross-Platform Build Systems:** Writing a robust `CMakeLists.txt` and utilizing `std::filesystem` for OS-independent file handling.
4. **Graphics & Rendering:** Integrating **SDL3** for rendering the pixel buffer (using XOR logic) and handling raw keyboard events.


