#ifndef _BUS_H
#define _BUS_H

#include <stdint.h>
#include "sm83.h"

#define GB_KiB 1024                 /* 1 Kibibyte in bytes */
#define GB_ROM00_SIZE (16 * GB_KiB) /* rom bank 00 size in bytes */

/**
 * A model of a GameBoy address bus.
 */
typedef struct GB_Bus
{
    GB_SM83 *sm83;
    uint8_t rom00[GB_ROM00_SIZE]; /* rom bank 00 */

} GB_Bus;

GB_Bus *gb_bus_create(GB_SM83 *sm83);
void gb_bus_destroy(GB_Bus *bus);

#endif