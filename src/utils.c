#include <stdint.h>

uint16_t gb_utils_u16_from_u8(uint8_t low, uint8_t high)
{
    return ((uint16_t)high << 8) | (uint16_t)low;
}

void gb_utils_u16_into_u8_pair(uint16_t u16, uint8_t *low, uint8_t *high)
{
    *high = (u16 & 0xff00) >> 8;
    *low = u16 & 0xff;
}