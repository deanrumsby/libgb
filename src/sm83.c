#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sm83.h"
#include "bus.h"
#include "instruction.h"
#include "utils.h"

static uint8_t gb_sm83_fetch(GB_SM83 *sm83);
static void gb_sm83_decode(GB_SM83 *sm83, GB_Instruction *instruction, uint8_t opcode);
static void gb_sm83_execute(GB_SM83 *sm83, GB_Instruction *instruction);

/**
 * Initializes an instance of a SM83 struct.
 * Takes a pointer to the address bus to allow memory read and writes.
 */
void gb_sm83_init(GB_SM83 *sm83, GB_Bus *bus)
{
    sm83->bus = bus;

    // registers
    sm83->pc = 0;
    sm83->sp = 0;
    sm83->a = 0;
    sm83->b = 0;
    sm83->c = 0;
    sm83->d = 0;
    sm83->e = 0;
    sm83->h = 0;
    sm83->l = 0;

    // flags
    sm83->Z = false;
    sm83->N = false;
    sm83->H = false;
    sm83->C = false;
}

/**
 * Steps the SM83 forward one execution cycle.
 */
void gb_sm83_step(GB_SM83 *sm83)
{
    uint8_t opcode = gb_sm83_fetch(sm83);

    GB_Instruction instruction;
    gb_sm83_decode(sm83, &instruction, opcode);

    gb_sm83_execute(sm83, &instruction);
}

/**
 * Fetches the next byte pointed at by the program counter.
 */
static uint8_t gb_sm83_fetch(GB_SM83 *sm83)
{
    uint8_t byte = gb_bus_read(sm83->bus, sm83->pc);
    sm83->pc += 1;

    return byte;
}

/**
 * Decodes the instruction.
 */
static void gb_sm83_decode(GB_SM83 *sm83, GB_Instruction *instruction, uint8_t opcode)
{
    gb_instruction_decode(instruction, opcode);

    for (int i = 1; i < instruction->length; i++)
    {
        instruction->bytes[i] = gb_sm83_fetch(sm83);
    }
}

/**
 * Executes an instruction.
 */
static void gb_sm83_execute(GB_SM83 *sm83, GB_Instruction *instruction)
{
    switch (instruction->type)
    {
    case GB_INSTRUCTION_UNDEFINED:
    // 00 NOP
    case GB_INSTRUCTION_NOP:
    {
        break;
    }
    // 01 LD BC, n16
    case GB_INSTRUCTION_LD_BC_N16:
    {
        sm83->b = instruction->bytes[1];
        sm83->c = instruction->bytes[2];
        break;
    }
    // 02 LD [BC], A
    case GB_INSTRUCTION_LD_MEM_BC_A:
    {
        uint16_t address = gb_utils_u16_from_u8(sm83->b, sm83->c);
        gb_bus_write(sm83->bus, address, sm83->a);
        break;
    }
    // 03 INC BC
    case GB_INSTRUCTION_INC_BC:
    {
        uint16_t value = gb_utils_u16_from_u8(sm83->b, sm83->c);
        value += 1;
        gb_utils_u16_into_u8_pair(value, &sm83->b, &sm83->c);
        break;
    }
    // 04 INC B
    case GB_INSTRUCTION_INC_B:
    {
        sm83->b += 1;
        sm83->Z = sm83->b == 0;
        sm83->N = false;
        sm83->H = sm83->b == 0x10; // lower nibble overflow from 0x0f -> 0x10
        break;
    }
    }
}