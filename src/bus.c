#include <stdint.h>
#include <stdlib.h>
#include "bus.h"
#include "sm83.h"

/**
 * Creates an instance of the bus on the heap.
 * Returns a pointer to the instance.
 */
GB_Bus *gb_bus_create()
{
    GB_Bus *bus = malloc(sizeof(GB_Bus));
    return bus;
}

/**
 * Destroys an instance of the bus.
 * All memory used on the heap is freed.
 */
void gb_bus_destroy(GB_Bus *bus)
{
    free(bus);
}

/**
 * Read a byte from a specified address on the bus.
 * Returns a 8-bit byte.
 *
 * TODO: this might be a redundant function if gb_bus_address_ptr_get is more useful
 */
uint8_t gb_bus_read(GB_Bus *bus, uint16_t address)
{
    if (address >= 0x0000 && address < 0x4000)
    {
        return bus->rom00[address];
    }

    return 0xcd;
}

/**
 * Finds the location of a provided 16-bit address and returns a pointer to it.
 */
uint8_t *gb_bus_address_ptr_get(GB_Bus *bus, uint16_t address)
{
    if (address >= 0x0000 && address < 0x4000)
    {
        return bus->rom00 + address;
    }
}
