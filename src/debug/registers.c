#include <stdint.h>
#include <stdbool.h>
#include <emscripten.h>
#include "gb.h"

/**
 * Gets the value of the 16-bit register PC.
 */
EMSCRIPTEN_KEEPALIVE
uint16_t gb_registers_pc_get(GB_GameBoy *gb)
{
    return gb->sm83->pc;
}

/**
 * Sets the value of the 16-bit register PC.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_pc_set(GB_GameBoy *gb, uint16_t value)
{
    gb->sm83->pc = value;
}

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

/**
 * Gets the state of the flag Z.
 */
EMSCRIPTEN_KEEPALIVE
bool gb_registers_flag_z_get(GB_GameBoy *gb)
{
    return gb->sm83->Z;
}

/**
 * Sets the state of the flag Z.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_flag_z_set(GB_GameBoy *gb, bool value)
{
    gb->sm83->Z = value;
}

/**
 * Gets the state of the flag N.
 */
EMSCRIPTEN_KEEPALIVE
bool gb_registers_flag_n_get(GB_GameBoy *gb)
{
    return gb->sm83->N;
}

/**
 * Sets the state of the flag N.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_flag_n_set(GB_GameBoy *gb, bool value)
{
    gb->sm83->N = value;
}

/**
 * Gets the state of the flag H.
 */
EMSCRIPTEN_KEEPALIVE
bool gb_registers_flag_h_get(GB_GameBoy *gb)
{
    return gb->sm83->H;
}

/**
 * Sets the state of the flag H.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_flag_h_set(GB_GameBoy *gb, bool value)
{
    gb->sm83->H = value;
}

/**
 * Gets the state of the flag C.
 */
EMSCRIPTEN_KEEPALIVE
bool gb_registers_flag_c_get(GB_GameBoy *gb)
{
    return gb->sm83->C;
}

/**
 * Sets the state of the flag C.
 */
EMSCRIPTEN_KEEPALIVE
void gb_registers_flag_c_set(GB_GameBoy *gb, bool value)
{
    gb->sm83->C = value;
}