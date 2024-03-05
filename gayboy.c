#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} FlagsRegister;

typedef struct
{
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    FlagsRegister F;
    uint8_t H;
    uint8_t L;
} Registers;

typedef struct
{
    Registers registers;
} CPU;

typedef enum
{
    ADD
} Instruction;

typedef enum
{
    A,
    B,
    C,
    D,
    E,
    F,
    H,
    L,
    BC,
    DE,
    HL,
    null
} ArithmeticTarget;

void set_16bit_register(Registers *registers, ArithmeticTarget reg1, ArithmeticTarget reg2, uint16_t value);
uint16_t get_16bit_register(Registers *registers, ArithmeticTarget reg1, ArithmeticTarget reg2);
uint8_t flags_to_8bit(FlagsRegister flagsregister);
FlagsRegister flags_from_8bit(uint8_t value);
void excecute(CPU *cpu, Instruction instruction, ArithmeticTarget target);
void add(Registers *registers, uint8_t value, bool *overflow);

uint16_t get_16bit_register(Registers *registers, ArithmeticTarget reg1, ArithmeticTarget reg2)
{
    uint16_t xy = 0;
    switch (reg1)
    {
    case A:
        xy = registers->A << 8;
        break;
    case B:
        xy = registers->B << 8;
        break;
    case C:
        xy = registers->C << 8;
        break;
    case D:
        xy = registers->D << 8;
        break;
    case E:
        xy = registers->E << 8;
        break;
    case F:
        xy = flags_to_8bit(registers->F) << 8;
        break;
    case H:
        xy = registers->H << 8;
        break;
    case L:
        xy = registers->L << 8;
        break;
    }
    switch (reg2)
    {
    case A:
        xy |= registers->A;
        break;
    case B:
        xy |= registers->B;
        break;
    case C:
        xy |= registers->C;
        break;
    case D:
        xy |= registers->D;
        break;
    case E:
        xy |= registers->E;
        break;
    case F:
        xy |= flags_to_8bit(registers->F);
        break;
    case H:
        xy |= registers->H;
        break;
    case L:
        xy |= registers->L;
        break;
    }
    return xy;
}

void set_16bit_register(Registers *registers, ArithmeticTarget reg1, ArithmeticTarget reg2, uint16_t value)
{
    switch (reg1)
    {
    case A:
        registers->A = (value & 0xFF00) >> 8;
        break;
    case B:
        registers->B = (value & 0xFF00) >> 8;
        break;
    case C:
        registers->C = (value & 0xFF00) >> 8;
        break;
    case D:
        registers->D = (value & 0xFF00) >> 8;
        break;
    case E:
        registers->E = (value & 0xFF00) >> 8;
        break;
    case F:
        registers->F = flags_from_8bit((value & 0xFF00) >> 8);
        break;
    case H:
        registers->H = (value & 0xFF00) >> 8;
        break;
    case L:
        registers->L = (value & 0xFF00) >> 8;
        break;
    }
    switch (reg2)
    {
    case A:
        registers->A = (value & 0xFF);
        break;
    case B:
        registers->B = (value & 0xFF);
        break;
    case C:
        registers->C = (value & 0xFF);
        break;
    case D:
        registers->D = (value & 0xFF);
        break;
    case E:
        registers->E = (value & 0xFF);
        break;
    case F:
        registers->F = flags_from_8bit(value & 0xFF);
        break;
    case H:
        registers->H = (value & 0xFF);
        break;
    case L:
        registers->L = (value & 0xFF);
        break;
    }
}

const uint8_t ZERO_FLAG_BYTE_POSITION = 7;
const uint8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const uint8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const uint8_t CARRY_FLAG_BYTE_POSITION = 4;

uint8_t flags_to_8bit(FlagsRegister flagsregister)
{
    uint8_t value = 0;
    if (flagsregister.zero)
        value |= (1 << ZERO_FLAG_BYTE_POSITION);
    if (flagsregister.subtract)
        value |= (1 << SUBTRACT_FLAG_BYTE_POSITION);
    if (flagsregister.half_carry)
        value |= (1 << HALF_CARRY_FLAG_BYTE_POSITION);
    if (flagsregister.carry)
        value |= (1 << CARRY_FLAG_BYTE_POSITION);
    return value;
}

FlagsRegister flags_from_8bit(uint8_t value)
{
    FlagsRegister instance = {false, false, false, false};
    instance.zero = (value >> ZERO_FLAG_BYTE_POSITION) & 1;
    instance.subtract = (value >> SUBTRACT_FLAG_BYTE_POSITION) & 1;
    instance.half_carry = (value >> HALF_CARRY_FLAG_BYTE_POSITION) & 1;
    instance.carry = (value >> CARRY_FLAG_BYTE_POSITION) & 1;
    return instance;
}

void excecute(CPU *cpu, Instruction instruction, ArithmeticTarget target)
{
    switch (instruction)
    {
    case ADD:
    {
        bool overflow = false;
        Registers *registers = &(cpu->registers);
        uint8_t value;
        switch (target)
        {
        case A:
        {
            value = registers->A;
            add(registers, value, &overflow);
            break;
        }
        case B:
        {
            value = registers->B;
            add(registers, value, &overflow);
            break;
        }
        case C:
        {
            value = registers->C;
            add(registers, value, &overflow);
            break;
        }
        case D:
        {
            value = registers->D;
            add(registers, value, &overflow);
            break;
        }
        case E:
        {
            value = registers->E;
            add(registers, value, &overflow);
            break;
        }
        case H:
        {
            value = registers->H;
            add(registers, value, &overflow);
            break;
        }
        case L:
        {
            value = registers->L;
            add(registers, value, &overflow);
            break;
        }
        case BC:
        {
            value = get_16bit_register(registers, B, C);
            add(registers, value, &overflow);
            break;
        }
        case DE:
        {
            value = get_16bit_register(registers, D, E);
            add(registers, value, &overflow);
            break;
        }
        case HL:
        {
            value = get_16bit_register(registers, H, L);
            add(registers, value, &overflow);
            break;
        }
        case null:
            break;
        }
        break;
    }
    }
}

void add(Registers *registers, uint8_t value, bool *overflow)
{
    uint8_t original = registers->A;
    uint8_t result = original + value;
    if (result < original || result < value)
        *overflow = true;
    registers->A = result;
    FlagsRegister *flags = &(registers->F);
    flags->zero = result == 0;
    flags->subtract = false;
    flags->carry = *overflow;
    flags->half_carry = ((original & 0xF) + (value & 0xF)) > 0xF;
}

int main()
{
    FlagsRegister flags = {false, false, false, false};
    Registers registers1 = {12, 0, 0, 0, 5, flags, 2, 1};
    CPU cpu1 = {registers1};
    excecute(&cpu1, ADD, HL);
    printf("register A: %d\n", cpu1.registers.A);
    printf("ZERO: %d\n", cpu1.registers.F.zero);
    printf("SUBTRACT: %d\n", cpu1.registers.F.subtract);
    printf("HALF-CARRY: %d\n", cpu1.registers.F.half_carry);
    printf("CARRY: %d\n", cpu1.registers.F.carry);
}
