#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bus.h"
#include "sm83.h"

#define GB_BUS_INVALID_READ_VALUE 0xcd /* a random value to help show invalid reads */

static bool gb_bus_address_writeable(uint16_t address);

/**
 * Reads the byte at a given 16-bit address in memory.
 */
uint8_t gb_bus_read(GB_Bus *bus, uint16_t address)
{
    uint8_t *ptr = gb_bus_address_ptr_get(bus, address);

    // invalid reads should not happen since the whole address space is mapped.
    // this check is here purely for use whilst building the project
    // and to ensure all control flows are handled.
    if (!ptr)
        return GB_BUS_INVALID_READ_VALUE;

    return *ptr;
}

/**
 * Writes a byte to the memory at a given 16-bit address, if writeable.
 */
void gb_bus_write(GB_Bus *bus, uint16_t address, uint8_t value)
{
    if (!gb_bus_address_writeable(address))
        return;

    uint8_t *ptr = gb_bus_address_ptr_get(bus, address);

    // this check might be redundant once the whole memory map is built
    if (ptr)
        *ptr = value;
}

/**
 * Checks if an address is writeable or not.
 */
static bool gb_bus_address_writeable(uint16_t address)
{
    // TODO: Update this with completed memory map values
    return address >= GB_BUS_VRAM_START && address <= GB_BUS_ECHO_RAM_END;
}

/**
 * Gets a pointer to a specific place in memory.
 */
uint8_t *gb_bus_address_ptr_get(GB_Bus *bus, uint16_t address)
{
    // ROM BANK 00
    if (address >= GB_BUS_ROM00_START && address <= GB_BUS_ROM00_END)
    {
        return bus->rom00 + address;
    }
    // ROM BANK 01
    else if (address >= GB_BUS_ROM01_START && address <= GB_BUS_ROM01_END)
    {
        return bus->rom01 + address - GB_BUS_ROM01_START;
    }
    // VRAM
    else if (address >= GB_BUS_VRAM_START && address <= GB_BUS_VRAM_END)
    {
        return bus->vram + address - GB_BUS_VRAM_START;
    }
    // EXTERNAL RAM
    else if (address >= GB_BUS_EXTERNAL_RAM_START && address <= GB_BUS_EXTERNAL_RAM_END)
    {
        return bus->eram00 + address - GB_BUS_EXTERNAL_RAM_START;
    }
    // WRAM BANK 00
    else if (address >= GB_BUS_WRAM00_START && address <= GB_BUS_WRAM00_END)
    {
        return bus->wram00 + address - GB_BUS_WRAM00_START;
    }
    // WRAM BANK 01
    else if (address >= GB_BUS_WRAM01_START && address <= GB_BUS_WRAM01_END)
    {
        return bus->wram01 + address - GB_BUS_WRAM01_START;
    }
    // ECHO RAM
    else if (address >= GB_BUS_ECHO_RAM_START && address <= GB_BUS_ECHO_RAM_END)
    {
        // this ram mirrors wram00 so just point there
        return bus->wram00 + address - GB_BUS_ECHO_RAM_START;
    }
    // this should be unreachable since all the 16-bit address space is mapped
    return NULL;
}