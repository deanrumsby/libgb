#include <stdint.h>

#define GB_MAX_INSTRUCTION_SIZE 3 /* maximum instruction size in bytes */

/**
 * The instruction types available.
 * Used as a tag to switch against.
 */
typedef enum
{
    GB_INSTRUCTION_UNDEFINED = 0, /* undefined */
    GB_INSTRUCTION_NOP,           /* nop */
    GB_INSTRUCTION_LD_BC_N16,     /* ld bc, n16 */

} GB_InstructionType;

/**
 * An instruction.
 * Contains a instruction type tag and holds the bytes of the original encoding
 * plus its length.
 */
typedef struct GB_Instruction
{
    GB_InstructionType type;
    int length;
    uint8_t bytes[GB_MAX_INSTRUCTION_SIZE];
} GB_Instruction;

static void gb_instruction_bytes_copy(uint8_t *source, uint8_t *dest, int count);

/**
 * Initializes an instruction.
 * Takes the three bytes (maximum) that encode the instruction and decodes them.
 */
void gb_instruction_init(GB_Instruction *instruction, uint8_t *bytes)
{
    int opcode = bytes[0];

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

    gb_instruction_bytes_copy(bytes, instruction->bytes, instruction->length);
}

static void gb_instruction_bytes_copy(uint8_t *source, uint8_t *dest, int count)
{
    for (int i = 0; i < count; i++)
    {
        dest[i] = source[i];
    }
}