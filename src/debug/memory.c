#include <stdint.h>
#include <stdbool.h>
#include <emscripten.h>
#include "gb.h"
#include "bus.h"

/**
 * Reads a value from memory.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t gb_memory_get(GB_GameBoy *gb, uint16_t address)
{
    return gb_bus_read(gb->bus, address);
}

/**
 * Sets the value at a given memory address.
 * This function ignores all write permissions i.e. read-only memory will be written to.
 */
EMSCRIPTEN_KEEPALIVE
void gb_memory_set(GB_GameBoy *gb, uint16_t address, uint8_t value)
{
    uint8_t *ptr = gb_bus_address_ptr_get(gb->bus, address);

    // this check might be redundant once the whole memory map is built
    if (ptr)
        *ptr = value;
}