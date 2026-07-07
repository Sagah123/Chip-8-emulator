cmake_minimum_required(VERSION 3.20)
project(Chip8Emulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем FetchContent для автозагрузки зависимостей
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.8
    GIT_SHALLOW TRUE  # Скачиваем быстро, без гигабайтов истории коммитов
)
FetchContent_MakeAvailable(SDL3)
add_executable(Chip8 
    src/main.cpp 
    src/Chip8.cpp
    src/Platform.cpp
    src/AppEngine.cpp
    src/EmulatorState.cpp
    include/Chip8.h
    include/Platform.h
)

target_include_directories(Chip8 PRIVATE include)
target_link_libraries(Chip8 PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(TARGET Chip8 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Chip8>
        $<TARGET_FILE_DIR:Chip8>
    )
endif()