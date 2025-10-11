#ifndef _BUS_H
#define _BUS_H

#include <stdint.h>

// TODO: maybe rename these macros to GB_BUS_... ?

#define GB_KiB 1024                            /* 1 kibibyte in bytes */
#define GB_ROM_BANK_SIZE (16 * GB_KiB)         /* rom bank size in bytes */
#define GB_VRAM_SIZE (8 * GB_KiB)              /* vram size in bytes */
#define GB_EXTERNAL_RAM_BANK_SIZE (8 * GB_KiB) /* external ram bank size in bytes */
#define GB_WRAM_BANK_SIZE (4 * GB_KiB)         /* wram bank size in bytes */

/**
 * A model of a GameBoy address bus.
 */
typedef struct GB_Bus
{
    uint8_t rom00[GB_ROM_BANK_SIZE];           /* rom bank 00 */
    uint8_t rom01[GB_ROM_BANK_SIZE];           /* rom bank 01 */
    uint8_t vram[GB_VRAM_SIZE];                /* vram */
    uint8_t eram00[GB_EXTERNAL_RAM_BANK_SIZE]; /* external ram bank 00 */
    uint8_t wram00[GB_WRAM_BANK_SIZE];         /* wram bank 00 */
    uint8_t wram01[GB_WRAM_BANK_SIZE];         /* wram bank 01 */

} GB_Bus;

uint8_t gb_bus_read(GB_Bus *bus, uint16_t address);
void gb_bus_write(GB_Bus *bus, uint16_t address, uint8_t value);

#endif