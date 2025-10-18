#include <stdint.h>
#include "instruction.h"

/**
 * Given an opcode, decodes the instruction type and length.
 * The opcode is inserted into the instruction's bytes array as the first element.
 * The rest of the instruction bytes must be appended manually.
 */
void gb_instruction_decode(GB_Instruction *instruction, uint8_t opcode)
{
    instruction->bytes[0] = opcode;

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
            instruction->t_cycles = 4;
            break;
        }
        case 0x1:
        {
            instruction->type = GB_INSTRUCTION_LD_BC_N16;
            instruction->length = 3;
            instruction->t_cycles = 12;
            break;
        }
        case 0x2:
        {
            instruction->type = GB_INSTRUCTION_LD_MEM_BC_A;
            instruction->length = 1;
            instruction->t_cycles = 8;
            break;
        }
        case 0x3:
        {
            instruction->type = GB_INSTRUCTION_INC_BC;
            instruction->length = 1;
            instruction->t_cycles = 8;
            break;
        }
        case 0x4:
        {
            instruction->type = GB_INSTRUCTION_INC_B;
            instruction->length = 1;
            instruction->t_cycles = 4;
            break;
        }
        case 0x5:
        {
            instruction->type = GB_INSTRUCTION_DEC_B;
            instruction->length = 1;
            instruction->t_cycles = 4;
            break;
        }
        default:
        {
            instruction->type = GB_INSTRUCTION_UNDEFINED;
            instruction->length = 1;
            instruction->t_cycles = 0; // TODO: think about this
            break;
        }
        }
        break;
    }
    default:
    {
        instruction->type = GB_INSTRUCTION_UNDEFINED;
        instruction->length = 1;
        instruction->t_cycles = 0; // TODO: think about this
        break;
    }
    }
}