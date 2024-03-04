#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

struct Registers{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t g;
    uint8_t h;
    uint8_t(*get_Registers)(struct Registers*)
};

uint16_t get_16bit_register(struct Registers* registers, char reg1, char reg2){
    uint16_t xy = 0;
    switch(reg1){
        case 'a': xy = registers->a << 8; break;
        case 'b': xy = registers->b << 8; break;
        case 'c': xy = registers->c << 8; break;
        case 'd': xy = registers->d << 8; break;
        case 'e': xy = registers->e << 8; break;
        case 'f': xy = registers->f << 8; break;
        case 'g': xy = registers->g << 8; break;
        case 'h': xy = registers->h << 8; break;
    }
    switch(reg2){
        case 'a': xy |= registers->a; break;
        case 'b': xy |= registers->b; break;
        case 'c': xy |= registers->c; break;
        case 'd': xy |= registers->d; break;
        case 'e': xy |= registers->e; break;
        case 'f': xy |= registers->f; break;
        case 'g': xy |= registers->g; break;
        case 'h': xy |= registers->h; break;
    }
    return xy;
}

void set_16bit_register(struct Registers* registers, char reg1, char reg2, uint16_t value){
    switch(reg1){
        case 'a': registers->a = (value & 0xFF00) >> 8; break;
        case 'b': registers->b = (value & 0xFF00) >> 8; break;
        case 'c': registers->c = (value & 0xFF00) >> 8; break;
        case 'd': registers->d = (value & 0xFF00) >> 8; break;
        case 'e': registers->e = (value & 0xFF00) >> 8; break;
        case 'f': registers->f = (value & 0xFF00) >> 8; break;
        case 'g': registers->g = (value & 0xFF00) >> 8; break;
        case 'h': registers->h = (value & 0xFF00) >> 8; break;
    }
    switch(reg2){
        case 'a': registers->a = (value & 0xFF); break;
        case 'b': registers->b = (value & 0xFF); break;
        case 'c': registers->c = (value & 0xFF); break;
        case 'd': registers->d = (value & 0xFF); break;
        case 'e': registers->e = (value & 0xFF); break;
        case 'f': registers->f = (value & 0xFF); break;
        case 'g': registers->g = (value & 0xFF); break;
        case 'h': registers->h = (value & 0xFF); break;
    }
}