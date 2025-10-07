#include <stdlib.h>
#include "bus.h"

/**
 * A model of a Game Boy handheld console.
 */
typedef struct GB_GameBoy
{
    GB_Bus *bus; /* 16-bit address bus */
} GB_GameBoy;

/**
 * Creates an instance of the Game Boy on the heap.
 * Creation also handles creating and composing instances of each internal
 * module that is required to emulate the handheld.
 * Returns a pointer to the instance.
 */
GB_GameBoy *gb_gameboy_create(void)
{
    GB_GameBoy *gb = malloc(sizeof(GB_GameBoy));
    GB_Bus *bus = gb_bus_create();

    gb->bus = bus;

    return gb;
}

/**
 * Destroys an instance of the Game Boy.
 * All memory used by the struct or any internal modules is freed.
 */
void gb_gameboy_destroy(GB_GameBoy *gb)
{
    gb_bus_destroy(gb->bus);
    free(gb);
}