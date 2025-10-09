#include <stdint.h>
#include <string.h>
#include "instructions.h"

/**
 * Initializes an instruction.
 * Takes the bytes (three maximum) that encode the instruction and decodes them.
 */
void gb_instruction_init(GB_Instruction *instruction, uint8_t *encoded_bytes)
{
    int opcode = encoded_bytes[0];

    int high = (opcode & 0xf0) >> 4; // high nibble from opcode
    int low = opcode & 0xf;          // low nibble from opcode

    switch (high)
    {
    case 0x0:
    {
        switch (low)
        {
        case 0x0:
        {
            instruction->type = GB_INSTRUCTION_NOP;
            instruction->length = 1;
            break;
        }
        case 0x1:
        {
            instruction->type = GB_INSTRUCTION_LD_BC_N16;
            instruction->length = 3;
        }
        }
        break;
    }
    }

    memcpy(instruction->bytes, encoded_bytes, instruction->length);
}