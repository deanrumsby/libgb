#include <stdint.h>
#include <stdio.h>
#include <emscripten.h>
#include "instruction.h"
#include "bus.h"
#include "gb.h"
#include "utils.h"

#define GB_DISASSEMBLY_LINE_MAX_LENGTH 30
#define GB_DISASSEMBLY_MAX_LINE_COUNT (2 * GB_ROM_BANK_SIZE)
#define GB_DISASSEMBLY_MAX_SIZE \
    (GB_DISASSEMBLY_LINE_MAX_LENGTH * GB_DISASSEMBLY_MAX_LINE_COUNT)

// TODO: the above GB_DISASSEMBLY_MAX_SIZE is a crude calculation that could be refined.

typedef struct GB_Disassembly
{
    char *text;
    int length;
} GB_Disassembly;

static int gb_disassembly_line_print(GB_Instruction *instruction, uint16_t address, char *buffer, int max_length);
static int gb_disassembly_line_append(GB_Disassembly *disassembly, char *line, int line_length);

/**
 * Takes an instance of the Game Boy and disassembles it's ROM.
 */
EMSCRIPTEN_KEEPALIVE
GB_Disassembly *gb_disassembly_create(GB_GameBoy *gb)
{
    GB_Disassembly *disassembly = malloc(sizeof(GB_Disassembly));
    disassembly->text = malloc(GB_DISASSEMBLY_MAX_SIZE);
    disassembly->length = 0;

    char line[GB_DISASSEMBLY_LINE_MAX_LENGTH];
    int line_length;

    uint16_t address = GB_BUS_ROM00_START;
    while (address <= GB_BUS_ROM01_END)
    {
        uint8_t opcode = gb_bus_read(gb->bus, address);
        GB_Instruction instruction;

        gb_instruction_decode(&instruction, opcode);

        for (int i = 0; i < instruction.length; i++)
            instruction.bytes[i] = gb_bus_read(gb->bus, address + i);

        line_length = gb_disassembly_line_print(&instruction, address, line, GB_DISASSEMBLY_LINE_MAX_LENGTH);
        gb_disassembly_line_append(disassembly, line, line_length);

        address += instruction.length;
    }

    disassembly->text[disassembly->length] = '\0';

    return disassembly;
}

/**
 * Prints an instruction as a line of disassembly to a provided buffer.
 */
static int gb_disassembly_line_print(GB_Instruction *instruction, uint16_t address, char *buffer, int max_length)
{
    int length = 0;
    uint8_t *bytes = instruction->bytes;

    switch (instruction->type)
    {
    case GB_INSTRUCTION_UNDEFINED:
    {
        length = snprintf(buffer, max_length, "%04X: %02X\tUNDEFINED\n", address, bytes[0]);
        break;
    }
    case GB_INSTRUCTION_NOP:
    {
        length = snprintf(buffer, max_length, "%04X: %02X\tNOP\n", address, bytes[0]);
        break;
    }
    case GB_INSTRUCTION_LD_BC_N16:
    {
        uint16_t n16 = gb_utils_u16_from_u8(bytes[1], bytes[2]);
        length = snprintf(buffer, max_length, "%04X: %02X%02X%02X\tLD BC, $%04X\n", address, bytes[0], bytes[1], bytes[2], n16);
        break;
    }
    case GB_INSTRUCTION_LD_MEM_BC_A:
    {
        length = snprintf(buffer, max_length, "%04X: %02X\tLD [BC], A\n", address, bytes[0]);
        break;
    }
    }

    return length;
}

/**
 * Appends a new line of disassembly to the currently processed disassembly string.
 */
static int gb_disassembly_line_append(GB_Disassembly *disassembly, char *line, int line_length)
{
    for (int i = 0; i < line_length; i++)
    {
        disassembly->text[disassembly->length] = line[i];
        disassembly->length += 1;
    }

    return disassembly->length;
}

/**
 * Frees the memory associated with the disassembly.
 */
EMSCRIPTEN_KEEPALIVE
void gb_disassembly_destroy(GB_Disassembly *disassembly)
{
    free(disassembly->text);
    free(disassembly);
}

/**
 * Returns a pointer to the disassembly text.
 */
EMSCRIPTEN_KEEPALIVE
char *gb_disassembly_text_get(GB_Disassembly *disassembly)
{
    return disassembly->text;
}

/**
 * Returns the length of the disassembly text.
 */
EMSCRIPTEN_KEEPALIVE
int gb_disassembly_length_get(GB_Disassembly *disassembly)
{
    return disassembly->length;
}
