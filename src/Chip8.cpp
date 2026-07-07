#include "Chip8.h"
#include <iostream>
#include <fstream>

Chip8::Chip8() :gen(rd()), distrib(0,255) {
    std::array<uint8_t, FONTSET_SIZE> fontset = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // Number 0
        0x20, 0x60, 0x20, 0x20, 0x70, // Number 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // Number 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // Number 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // Number 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // Number 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // Number 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // Number 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // Number 8   
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // Number 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // Letter A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // Letter B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // Letter C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // Letter D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // Letter E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // Letter F
    };
    for (int i = 0; i < 80; i++){
        memory[FONTSET_START_ADDRESS+i] = fontset[i];
    }
}

bool Chip8::loadROM(const std::string& filename){
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return false;
    }
    auto fileSize = file.tellg();
    if (fileSize > (Chip8::memory.size() - START_ADDRESS)) {
        throw std::runtime_error("ROM size exceeds available memory.");
    }
    file.seekg(0);  
    file.read(reinterpret_cast<char*>(&memory[START_ADDRESS]), fileSize);
    file.close();
    return true;
}

void Chip8::emulateCycle(){
    // ==========================================
    // 1. FETCH
    // ==========================================
    uint16_t command = (memory[pc] << 8) | memory[pc+1];
    pc += 2;

    // ==========================================
    // 2. DISMEMBER
    // ==========================================
    uint8_t prefix = (command & 0xF000) >> 12;
    uint8_t x = (command & 0x0F00) >> 8;
    uint8_t y = (command & 0x00F0) >> 4;
    uint8_t N = (command & 0x000F);
    uint8_t NN = (command & 0x00FF);
    uint16_t NNN = (command & 0x0FFF);

    // ==========================================
    // 3. EXECUTE
    // ==========================================
    uint8_t flag = 0;
    switch (prefix)
    {
    case 0x0:
        switch (NN)
        {
        case 0xEE:
            //return from subroutine call
            sp--;
            pc = stack[sp];
            break;
        case 0xE0:
            //clear the screen
            for (auto& row: display){
                for (auto& pixel: row){
                    pixel = 0;
                }
            }
            drawFlag = true;
        }
        break;
    case 0x1:
        //jump to NNN
        pc = NNN;
        break;
    case 0x2:
        //jump a subroutine
        stack[sp] = pc;
        sp++;
        pc = NNN;
        break;
    case 0x3:
        //skip if vx equals NN
        if (V[x] == NN) pc +=2;
        break;
    case 0x4:
        //skip if vx not equals NN 
        if (V[x] != NN) pc +=2;
        break;
    case 0x5:
        //skip if vx equals vy
        if (N == 0 && V[x] == V[y]) pc += 2;
        break;
    case 0x6:
        //move constant to register vx
        V[x] = NN;
        break;
    case 0x7:
        //add constant to register vx (No carry :{ )
        V[x] += NN;
        break;
    case 0x8:
        //ALU
        switch (N)
        {
        case 0x0:
            // vx = vy
            V[x] = V[y];
            break;
        case 0x1:
            //or register vy into register vx
            V[x] |= V[y];
            break;
        case 0x2:
            //and register vy into register vx
            V[x] &= V[y];
            break;
        case 0x3:
            //xor register vy into register vx
            V[x] ^= V[y];
            break;
        case 0x4:{
            //add register vy into register vx, carry in vf
            uint16_t result = V[x]+ V[y];
            if (result > 255) V[15] = 1;
            else V[15] = 0;
            flag = V[15];
            V[x] = result & 0xFF;
            V[15] = flag;
            break;
        }
        case 0x5:
            //substract register vy from register vx, borrow in vf
            if (V[y]>V[x]) V[15] = 0;
            else V[15] = 1;
            flag = V[15];
            V[x] = V[x] - V[y];
            V[15] = flag;
            break;
        case 0x6:
            //shift register vx right, bit 0 goes into register vf
           V[15] = V[x] & 0x1;
            V[x] >>= 1;
            break;
        case 0x7:
            //substract register vx from register vy, borrow in vf (reversed 0x5 operation)
            if (V[x]>V[y]) V[15] = 0;
            else V[15] = 1;
            flag = V[15];
            V[x] = V[y] - V[x];
            V[15] = flag;
            break;
            break;
        case 0xe:
            //shift register vx left,bit 7 goes into regisxter vf
            V[15] = (V[x] & 0x80) >> 0x7;
            V[x] <<= 1;
            break;
    }
    break;
    case 0x9:
        //skip if vx not equals vy
        if (N == 0 && V[x] != V[y]) pc += 2;
        break;
    case 0xa:
        //load index register with NNN
        I = NNN;
        break;
    case 0xb:
        //Jump to address NNN+register
        pc = V[0] + NNN;
        break;
    case 0xc:
        //random number between 0 and 255 inclusive AND NNN
        V[x] = distrib(gen) & NN;
        break;
    case 0xd:{
        //Draw sprite at screen location rx,ry height s 
        V[15] = 0;
        uint16_t startX = V[x] % VIDEO_WIDTH;
        uint16_t startY = V[y] % VIDEO_HEIGHT;
        for (int row = 0;row < N; row++){
            uint8_t spriteByte = memory[I+row];
            uint16_t currY = (startY + row) % VIDEO_HEIGHT;
            for (int col = 0; col < 8;col++){
                if (spriteByte & ( 0x80 >> col)){
                    uint16_t currX = (startX + col) % VIDEO_WIDTH;
                    if (display[currY][currX] == 1){
                         V[15] = 1;
                    }
                    display[currY][currX] ^=  1;
                    }
                }
            }
        drawFlag = true;
        break;
        }
    case 0xe:
        switch(NN){
            case 0x9e:{
                //skip if key is pressed
                if (keypad[V[x]]) pc +=2;
                break;
            }
            case 0xa1:{
                //skip if key isnt pressed
                if (!keypad[V[x]]) pc +=2;
                break;
            }
        }

        break;
    case 0xf:
        //various functions
        switch(NN){
            case 0x7:
            //put delay in vx
                V[x] = delay_timer;
                break;
            case 0xa:{
                //wait for a keypress
                bool keyPressed = false;
                for (int i = 0;i < 16;i++){
                    if (keypad[i]){
                        V[x] = i;
                        keyPressed = true;
                        break;
                    }
                }
                if (!keyPressed) pc -= 2;
                break;
            }
            case 0x15:
                //put vx in delay
                delay_timer = V[x];
                break;
            case 0x18:
                //put vx in buzzer
                sound_timer = V[x];
                break;
            case 0x1e:
                //add vx to I
                I += V[x];
                break;
            case 0x29:
                //set i to hex char
                I = 0x50 + 5 * V[x];
                break;
            case 0x33:{
                //bcd
                uint8_t value = V[x];
                memory[I] = value / 100;
                memory[I+1] = (value / 10) % 10;
                memory[I+2] = value % 10;
                break;
            }
            case 0x55:
                //save vx
                for (int i = 0; i <= x; i++){
                    memory[I+i] = V[i];
                }
                I += x + 1;
                break;
            case 0x65:
                //load vx
                for (int i = 0; i <=x ; i++){
                    V[i] = memory[I+i];
                }
                I += x + 1;
                break;
        }
        
        break;
    default:
        //Undefined instruction
        break;
    }
}
