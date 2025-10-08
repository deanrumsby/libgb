#include <stdint.h>
#include <stdlib.h>
#include "bus.h"
#include "sm83.h"

/**
 * Creates an instance of the bus on the heap.
 * Returns a pointer to the instance.
 */
GB_Bus *gb_bus_create(GB_SM83 *sm83)
{
    GB_Bus *bus = malloc(sizeof(GB_Bus));
    bus->sm83 = sm83;
    return bus;
}

/**
 * Destroys an instance of the bus.
 * All memory used on the heap is freed.
 */
void gb_bus_destroy(GB_Bus *bus)
{
    gb_sm83_destroy(bus->sm83);
    free(bus);
}

/**
 * Read a byte from a specified address on the bus.
 * Returns a 8-bit byte.
 */
uint8_t gb_bus_read(GB_Bus *bus, uint16_t address)
{
    if (address >= 0x0000 && address < 0x4000)
    {
        return bus->rom00[address];
    }

    return 0xcd;
}
