#include <stdint.h>
#include <emscripten.h>
#include "gb.h"
#include "bus.h"

EMSCRIPTEN_KEEPALIVE
uint8_t gb_memory_get(GB_GameBoy *gb, uint16_t address)
{
    return gb_bus_read(gb->bus, address);
}