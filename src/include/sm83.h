#ifndef _SM83_H
#define _SM83_H

#include <stdint.h>
#include <stdbool.h>
#include "bus.h"

/**
 * A model of a Sharp SM83 CPU core.
 */
typedef struct GB_SM83
{
    GB_Bus *bus; /* a pointer to the 16-bit address bus */

    uint16_t pc; /* program counter register */
    uint16_t sp; /* stack pointer register */

    uint8_t a; /* accumulator register */
    uint8_t b; /* b register */
    uint8_t c; /* c register */
    uint8_t d; /* d register */
    uint8_t e; /* e register */
    uint8_t h; /* h register */
    uint8_t l; /* l register */

    bool Z; /* zero flag */
    bool N; /* negative flag */
    bool H; /* half carry flag */
    bool C; /* carry flag */
} GB_SM83;

void gb_sm83_init(GB_SM83 *sm83, GB_Bus *bus);
void gb_sm83_step(GB_SM83 *sm83);

#endif