#include <stdlib.h>
#include <emscripten.h>
#include "gb.h"
#include "bus.h"
#include "sm83.h"

/**
 * Creates an instance of the Game Boy on the heap.
 * Creation also handles creating and composing instances of each internal
 * module that is required to emulate the handheld.
 * Returns a pointer to the instance.
 */
EMSCRIPTEN_KEEPALIVE
GB_GameBoy *gb_gameboy_create(void)
{
    GB_GameBoy *gb = malloc(sizeof(GB_GameBoy));

    GB_Bus *bus = malloc(sizeof(GB_Bus));
    GB_SM83 *sm83 = malloc(sizeof(GB_SM83));

    gb_sm83_init(sm83, bus);

    gb->bus = bus;
    gb->sm83 = sm83;

    return gb;
}

/**
 * Destroys an instance of the Game Boy.
 * All memory used by the struct or any internal modules is freed.
 */
EMSCRIPTEN_KEEPALIVE
void gb_gameboy_destroy(GB_GameBoy *gb)
{
    free(gb->sm83);
    free(gb->bus);

    free(gb);
}

/**
 * Returns a pointer to ROM bank 00.
 * Used when loading in a rom from JavaScript.
 */
EMSCRIPTEN_KEEPALIVE
uint8_t *gb_gameboy_rom_ptr_get(GB_GameBoy *gb)
{
    return gb->bus->rom00;
}

/**
 * Returns the size of ROM bank 00.
 * Used as a guard when loading in a rom from JavaScript.
 */
EMSCRIPTEN_KEEPALIVE
int gb_gameboy_rom_size_get()
{
    return GB_ROM00_SIZE;
}

/**
 * Steps the SM83 through one machine cycle.
 */
EMSCRIPTEN_KEEPALIVE
void gb_gameboy_step(GB_GameBoy *gb)
{
    gb_sm83_step(gb->sm83);
}