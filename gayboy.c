#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} FlagsRegister;

typedef struct{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    FlagsRegister f;
    uint8_t g;
    uint8_t h;
} Registers;

uint16_t get_16bit_register(Registers *registers, char reg1, char reg2){
    uint16_t xy = 0;
    switch(reg1){
        case 'a': xy = registers->a << 8; break;
        case 'b': xy = registers->b << 8; break;
        case 'c': xy = registers->c << 8; break;
        case 'd': xy = registers->d << 8; break;
        case 'e': xy = registers->e << 8; break;
        case 'f': xy = flags_to_8bit(registers->f) << 8; break;
        case 'g': xy = registers->g << 8; break;
        case 'h': xy = registers->h << 8; break;
    }
    switch(reg2){
        case 'a': xy |= registers->a; break;
        case 'b': xy |= registers->b; break;
        case 'c': xy |= registers->c; break;
        case 'd': xy |= registers->d; break;
        case 'e': xy |= registers->e; break;
        case 'f': xy |= flags_to_8bit(registers->f); break;
        case 'g': xy |= registers->g; break;
        case 'h': xy |= registers->h; break;
    }
    return xy;
}

void set_16bit_register(Registers *registers, char reg1, char reg2, uint16_t value){
    switch(reg1){
        case 'a': registers->a = (value & 0xFF00) >> 8; break;
        case 'b': registers->b = (value & 0xFF00) >> 8; break;
        case 'c': registers->c = (value & 0xFF00) >> 8; break;
        case 'd': registers->d = (value & 0xFF00) >> 8; break;
        case 'e': registers->e = (value & 0xFF00) >> 8; break;
        case 'f': registers->f = flags_from_8bit((value & 0xFF00) >> 8); break;
        case 'g': registers->g = (value & 0xFF00) >> 8; break;
        case 'h': registers->h = (value & 0xFF00) >> 8; break;
    }
    switch(reg2){
        case 'a': registers->a = (value & 0xFF); break;
        case 'b': registers->b = (value & 0xFF); break;
        case 'c': registers->c = (value & 0xFF); break;
        case 'd': registers->d = (value & 0xFF); break;
        case 'e': registers->e = (value & 0xFF); break;
        case 'f': registers->f = flags_from_8bit(value & 0xFF); break;
        case 'g': registers->g = (value & 0xFF); break;
        case 'h': registers->h = (value & 0xFF); break;
    }
}

const uint8_t ZERO_FLAG_BYTE_POSITION = 7;
const uint8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const uint8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const uint8_t CARRY_FLAG_BYTE_POSITION = 4;

uint8_t flags_to_8bit(FlagsRegister flagsregister){
    uint8_t value = 0;
    if(flagsregister.zero) value |= (1 << ZERO_FLAG_BYTE_POSITION);
    if(flagsregister.subtract) value |= (1 << SUBTRACT_FLAG_BYTE_POSITION);
    if(flagsregister.half_carry) value |= (1 << HALF_CARRY_FLAG_BYTE_POSITION);
    if(flagsregister.carry) value |= (1 << CARRY_FLAG_BYTE_POSITION);
    return value;
}

FlagsRegister flags_from_8bit(uint8_t value){
    FlagsRegister instance = {false, false, false, false};
    instance.zero = (value >> ZERO_FLAG_BYTE_POSITION) & 1;
    instance.subtract = (value >> SUBTRACT_FLAG_BYTE_POSITION) & 1;
    instance.half_carry = (value >> HALF_CARRY_FLAG_BYTE_POSITION) & 1;
    instance.carry = (value >> CARRY_FLAG_BYTE_POSITION) & 1;
    return instance;
}
