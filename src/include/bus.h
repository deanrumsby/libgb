#ifndef _BUS_H
#define _BUS_H

#include <stdint.h>

#define GB_KiB 1024                 /* 1 Kibibyte in bytes */
#define GB_ROM00_SIZE (16 * GB_KiB) /* rom bank 00 size in bytes */

/**
 * A model of a GameBoy address bus.
 */
typedef struct GB_Bus
{
    uint8_t rom00[GB_ROM00_SIZE]; /* rom bank 00 */

} GB_Bus;

uint8_t gb_bus_read(GB_Bus *bus, uint16_t address); // TODO: this might be an irrelevant function
uint8_t *gb_bus_address_ptr_get(GB_Bus *bus, uint16_t address);

#endif