#include <stdint.h>

uint16_t gb_utils_u16_from_u8(uint8_t high, uint8_t low)
{
    return (high << 4) & low;
}