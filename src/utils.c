#include <stdint.h>

uint16_t gb_utils_u16_from_u8(uint8_t high, uint8_t low)
{
    return ((uint16_t)high << 8) | (uint16_t)low;
}