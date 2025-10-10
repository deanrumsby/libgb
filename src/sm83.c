#include <stdint.h>
#include <stdlib.h>
#include "sm83.h"
#include "bus.h"
#include "instruction.h"

static void gb_sm83_execute(GB_SM83 *sm83, GB_Instruction *instruction);

/**
 * Initializes an instance of a SM83 struct.
 * Takes a pointer to the address bus to allow memory read and writes.
 */
void gb_sm83_init(GB_SM83 *sm83, GB_Bus *bus)
{
    sm83->bus = bus;

    sm83->pc = 0;
    sm83->sp = 0;
    sm83->a = 0;
    sm83->b = 0;
    sm83->c = 0;
    sm83->d = 0;
    sm83->e = 0;
    sm83->h = 0;
    sm83->l = 0;
    sm83->f = 0;
}

/**
 * Steps the SM83 forward one execution cycle.
 */
void gb_sm83_step(GB_SM83 *sm83)
{
    uint8_t *encoded_bytes = gb_bus_address_ptr_get(sm83->bus, sm83->pc);

    GB_Instruction instruction;
    gb_instruction_fetch(&instruction, encoded_bytes);

    sm83->pc += instruction.length;

    gb_sm83_execute(sm83, &instruction);
}

/**
 * Executes an instruction.
 */
static void gb_sm83_execute(GB_SM83 *sm83, GB_Instruction *instruction)
{
    switch (instruction->type)
    {
    case GB_INSTRUCTION_UNDEFINED:
    case GB_INSTRUCTION_NOP:
    {
        break;
    }
    case GB_INSTRUCTION_LD_BC_N16:
    {
        sm83->b = instruction->bytes[1];
        sm83->c = instruction->bytes[2];
        break;
    }
    }
}