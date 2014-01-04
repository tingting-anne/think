#include <limits.h>
#include <stdarg.h>

#include "bloom.h"
#include "bitops.h"
 
BLOOM *bloom_create(size_t size, size_t nfuncs, ...)
{
    BLOOM *bloom;
    va_list list;
    size_t n;
    
    if(!(bloom = (BLOOM*)malloc(sizeof(BLOOM)))){
       return NULL;
    }
    if(!(bloom->bits = (unsigned char*)calloc((size+BITS_PER_BYTE-1)/BITS_PER_BYTE, sizeof(char)))) {
       goto free_bloom;
    }
    if(!(bloom->funcs = (hashfunc_t*)malloc(nfuncs*sizeof(hashfunc_t)))) {
        goto free_bits;
    }

    va_start(list, nfuncs);
    for(n=0; n < nfuncs; ++n) {
        bloom->funcs[n] = va_arg(list, hashfunc_t);
    }
    va_end(list);

    bloom->nfuncs = nfuncs;
    bloom->bitsize = size;
    return bloom;
    
free_bits:
    free(bloom->bits);
free_bloom:
    free(bloom);
    return NULL;
}

int bloom_destroy(BLOOM *bloom)
{
    free(bloom->bits);
    free(bloom->funcs);
    free(bloom);

    return 0;
}

int bloom_add(BLOOM *bloom, const char *s)
{
    size_t n;

    for(n=0; n < bloom->nfuncs; ++n) {
        set_bit(bloom->funcs[n](s)% bloom->bitsize, bloom->bits);
    }

    return 0;
}

int bloom_check(BLOOM *bloom, const char *s)
{
    size_t n;

    for(n=0; n < bloom->nfuncs; ++n) {
        if(!(test_bit(bloom->funcs[n](s)% bloom->bitsize, bloom->bits))){
         return 0;
        }
    }

    return 1;
}
