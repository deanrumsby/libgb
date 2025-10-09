#ifndef _SM83_H
#define _SM83_H

#include <stdint.h>
#include "bus.h"

/**
 * A model of a Sharp SM83 CPU core.
 */
typedef struct GB_SM83
{
    uint16_t pc; /* program counter register */
    uint16_t sp; /* stack pointer register */

    uint8_t a; /* accumulator register */
    uint8_t b; /* b register */
    uint8_t c; /* c register */
    uint8_t d; /* d register */
    uint8_t e; /* e register */
    uint8_t h; /* h register */
    uint8_t l; /* l register */
    uint8_t f; /* flags register */
} GB_SM83;

GB_SM83 *gb_sm83_create(GB_Bus *bus);
void gb_sm83_destroy(GB_SM83 *sm83);

void gb_sm83_step(GB_SM83 *sm83);

#endif