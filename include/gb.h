#ifndef _GB_H
#define _GB_H

typedef void GB_GameBoy;

GB_GameBoy *gb_gameboy_create(void);
void gb_gameboy_destroy(GB_GameBoy *gb);

#endif