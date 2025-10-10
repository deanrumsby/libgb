#include <stdint.h>
#include <stdlib.h>
#include "bus.h"
#include "sm83.h"

#define GB_ROM00_START 0
#define GB_ROM00_END 0x3fff

#define GB_ROM01_START 0x4000
#define GB_ROM01_END 0x7fff

#define GB_VRAM_START 0x8000
#define GB_VRAM_END 0x9fff

#define GB_EXTERNAL_RAM_START 0xa000
#define GB_EXTERNAL_RAM_END 0xbfff

#define GB_WRAM00_START 0xc000
#define GB_WRAM00_END 0xcfff

#define GB_WRAM01_START 0xd000
#define GB_WRAM01_END 0xdfff

#define GB_ECHO_RAM_START 0xe000
#define GB_ECHO_RAM_END 0xfdff

/**
 * Finds the location of a provided 16-bit address and returns a pointer to it.
 */
uint8_t *gb_bus_address_ptr_get(GB_Bus *bus, uint16_t address)
{
    // ROM BANK 00
    if (address >= GB_ROM00_START && address <= GB_ROM00_END)
    {
        return bus->rom00 + address;
    }
    // ROM BANK 01
    else if (address >= GB_ROM01_START && address <= GB_ROM01_END)
    {
        return bus->rom01 + address - GB_ROM01_START;
    }
    // VRAM
    else if (address >= GB_VRAM_START && address <= GB_VRAM_END)
    {
        return bus->vram + address - GB_VRAM_START;
    }
    // EXTERNAL RAM
    else if (address >= GB_EXTERNAL_RAM_START && address <= GB_EXTERNAL_RAM_END)
    {
        return bus->eram00 + address - GB_EXTERNAL_RAM_START;
    }
    // WRAM BANK 00
    else if (address >= GB_WRAM00_START && address <= GB_WRAM00_END)
    {
        return bus->wram00 + address - GB_WRAM00_START;
    }
    // WRAM BANK 01
    else if (address >= GB_WRAM01_START && address <= GB_WRAM01_END)
    {
        return bus->wram01 + address - GB_WRAM01_START;
    }
    // ECHO RAM
    else if (address >= GB_ECHO_RAM_START && address <= GB_ECHO_RAM_END)
    {
        // this ram mirrors wram00 so just point there
        return bus->wram00 + address - GB_ECHO_RAM_START;
    }
}
