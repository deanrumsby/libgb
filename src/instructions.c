#include <stdint.h>

#define GB_MAX_INSTRUCTION_SIZE 3 /* maximum instruction size in bytes */

/**
 * The instruction types available.
 * Used as a tag to switch against.
 */
typedef enum
{
    GB_INSTRUCTION_UNKNOWN = 0,  /* not a defined instruction */
    GB_INSTRUCTION_NOP,          /* nop */
    GB_INSTRUCTION_LD_R16_IMM16, /* ld r16, imm16 */
    GB_INSTRUCTION_LD_R16MEM_A,  /* ld [r16mem], a */
    GB_INSTRUCTION_LD_A_R16MEM,  /* ld a, [r16mem] */
    GB_INSTRUCTION_LD_IMM16_SP,  /* ld [imm16], sp */
} GB_InstructionType;

/**
 * An instruction.
 * Contains a instruction type tag and holds the potential
 * bytes used as arguments.
 * These arguments are not always used and so will sometimes contain uninitialized values.
 */
typedef struct GB_Instruction
{
    GB_InstructionType type;
    uint8_t arguments[2];
} GB_Instruction;

/**
 * Initializes an instruction.
 * Takes the three bytes (maximum) that encode the instruction and
 * decodes them into an instruction type and potential arguments.
 * All three bytes are not always used.
 */
void gb_instruction_init(GB_Instruction *instruction, uint8_t bytes[GB_MAX_INSTRUCTION_SIZE])
{
    int opcode = bytes[0];
    int block = (opcode & 0xc0) >> 6; // applys the mask 0b11000000

    switch (block)
    {
    case 0x0:
    {
        switch (opcode & 0x3f) // applys the mask 0b00111111;
        {
        case 0x0: // 00000000
        {
            instruction->type = GB_INSTRUCTION_NOP;
            break;
        }
        case 0x8: // 00001000
        {
            instruction->type = GB_INSTRUCTION_LD_IMM16_SP;
            instruction->arguments[0] = bytes[1];
            instruction->arguments[1] = bytes[2];
            break;
        }
        default:
        {
            switch (opcode & 0xf) // applys the mask 0b00001111
            {
            case 0x1: // 00##0001
            {
                instruction->type = GB_INSTRUCTION_LD_R16_IMM16;
                instruction->arguments[0] = bytes[1];
                instruction->arguments[1] = bytes[2];
                break;
            }
            case 0x2: // 00##0010
            {
                instruction->type = GB_INSTRUCTION_LD_R16MEM_A;
                break;
            }
            case 0xa: // 00##1010
            {
                instruction->type = GB_INSTRUCTION_LD_A_R16MEM;
                break;
            }
            default:
            {
                instruction->type = GB_INSTRUCTION_UNKNOWN;
                break;
            }
            }
            break;
        }
        }
        break;
    }
    default:
    {
        instruction->type = GB_INSTRUCTION_UNKNOWN;
        break;
    }
    }
}