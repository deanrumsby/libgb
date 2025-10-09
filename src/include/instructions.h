#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

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

void gb_instruction_init(GB_Instruction *instruction, uint8_t *bytes);

#endif