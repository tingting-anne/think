#include "inttype.h"
/* 2^31 + 2^29 - 2^25 + 2^22 - 2^19 - 2^16 + 1 */
#define GOLDEN_RATIO_PRIME_32       0x9e370001UL

/* *
 * hash32 - generate a hash value in the range [0, 2^@bits - 1]
 * @val:    the input value
 * @bits:   the number of bits in a return value
 *
 * High bits are more random, so we use them.
 * */
uint hash32(uint val, unsigned int bits) {
    uint hash = val * GOLDEN_RATIO_PRIME_32;
    return (hash >> (32 - bits));
}

