#include <stdint.h>
#include <stdlib.h>
#include "bus.h"
#include "instructions.h"

/**
 * A model of a Sharp SM83 CPU core.
 */
typedef struct GB_SM83
{
    GB_Bus *bus; /* a pointer to the 16-bit address bus */

    uint16_t pc; /* program counter register */
    uint16_t sp; /* stack pointer register */

    uint8_t a; /* accumulator register */
    uint8_t b; /* b register */
    uint8_t c; /* c register */
    uint8_t d; /* d register */
    uint8_t e; /* e register */
    uint8_t h; /* h register */
    uint8_t l; /* l register */
    uint8_t f; /* flags register */
} GB_SM83;

static void gb_sm83_execute(GB_SM83 *sm83, GB_Instruction *instruction);

/**
 * Creates an instance of the SM83 on the heap.
 * Takes a pointer to the address bus to allow memory read and writes.
 * Returns a pointer to the instance.
 */
GB_SM83 *gb_sm83_create(GB_Bus *bus)
{
    GB_SM83 *sm83 = malloc(sizeof(GB_SM83));

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

    return sm83;
}

/**
 * Destroys an instance of the SM83.
 * All memory used on the heap is freed.
 */
void gb_sm83_destroy(GB_SM83 *sm83)
{
    free(sm83);
}

void gb_sm83_step(GB_SM83 *sm83)
{
    uint8_t *encoded_bytes = gb_bus_address_ptr_get(sm83->bus, sm83->pc);

    GB_Instruction instruction;
    gb_instruction_init(&instruction, encoded_bytes);
}

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