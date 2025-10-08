#ifndef _GB_H
#define _GB_H

#include "bus.h"

/**
 * A model of a Game Boy handheld console.
 */
typedef struct GB_GameBoy
{
    GB_Bus *bus; /* 16-bit address bus */
} GB_GameBoy;

#endif