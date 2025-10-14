#include <stdint.h>
#include <emscripten.h>
#include "gb.h"

/**
 * Gets the value of the 8-bit register A.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t gb_registers_a_get(GB_GameBoy *gb)
{
    return gb->sm83->a;
}

/**
 * Sets the value of the 8-bit register A.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_a_set(GB_GameBoy *gb, uint8_t value)
{
    gb->sm83->a = value;
}

/**
 * Gets the value of the 8-bit register B.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t gb_registers_b_get(GB_GameBoy *gb)
{
    return gb->sm83->b;
}

/**
 * Sets the value of the 8-bit register B.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_b_set(GB_GameBoy *gb, uint8_t value)
{
    gb->sm83->b = value;
}

/**
 * Gets the value of the 8-bit register C.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t gb_registers_c_get(GB_GameBoy *gb)
{
    return gb->sm83->c;
}

/**
 * Sets the value of the 8-bit register B.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_c_set(GB_GameBoy *gb, uint8_t value)
{
    gb->sm83->c = value;
}