#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

#define GB_INSTRUCTION_MAX_SIZE 3 /* maximum instruction size in bytes */

/**
 * The instruction types available.
 * Used as a tag to switch against.
 */
typedef enum
{
    GB_INSTRUCTION_UNDEFINED = 0, /* undefined */
    GB_INSTRUCTION_NOP,           /* 00 NOP */
    GB_INSTRUCTION_LD_BC_N16,     /* 01 LD BC, n16 */
    GB_INSTRUCTION_LD_MEM_BC_A,   /* 02 LD [BC], A */
    GB_INSTRUCTION_INC_BC,        /* 03 INC BC */
    GB_INSTRUCTION_INC_B,         /* 04 INC B */
    GB_INSTRUCTION_DEC_B,         /* 05 DEC B */

} GB_InstructionType;

/**
 * An instruction.
 * Contains a instruction type tag and holds the bytes of the original encoding,
 * plus its length and the number of t-cycles it takes to execute.
 */
typedef struct GB_Instruction
{
    GB_InstructionType type;
    int length;
    int t_cycles;
    uint8_t bytes[GB_INSTRUCTION_MAX_SIZE];
} GB_Instruction;

void gb_instruction_decode(GB_Instruction *instruction, uint8_t opcode);

#endif