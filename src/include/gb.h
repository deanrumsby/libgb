#ifndef _GB_H
#define _GB_H

#include "sm83.h"
#include "bus.h"

/**
 * A model of a Game Boy handheld console.
 */
typedef struct GB_GameBoy
{
    GB_SM83 *sm83; /* Sharp SM83 CPU Core*/
    GB_Bus *bus;   /* 16-bit address bus */
} GB_GameBoy;

#endif