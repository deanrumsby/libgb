#include <stdint.h>
#include <stdlib.h>

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

/**
 * Creates an instance of the SM83 on the heap.
 * Returns a pointer to the instance.
 */
GB_SM83 *gb_sm83_create(void)
{
    GB_SM83 *sm83 = malloc(sizeof(GB_SM83));
    sm83->pc = 0;
    sm83->sp = 0;
    sm83->a = 0;
    sm83->b = 0;
    sm83->c = 0;
    sm83->d = 0;
    sm83->e = 0;
    sm83->h = 0;
    sm83->l = 0;
    sm83->f = 0;

    return sm83;
}

/**
 * Destroys an instance of the SM83.
 * All memory used on the heap is freed.
 */
void gb_sm83_destroy(GB_SM83 *sm83)
{
    free(sm83);
}