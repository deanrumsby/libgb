#include <stdint.h>
#include <emscripten.h>
#include "gb.h"

/**
 * Gets the value of the 8-bit register B.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t gb_registers_b_get(GB_GameBoy *gb)
{
    return gb->sm83->b;
}

/**
 * Gets the value of the 8-bit register C.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t gb_registers_c_get(GB_GameBoy *gb)
{
    return gb->sm83->c;
}