#ifndef _THINK_LINUX_BITOPS_H_
#define _THINK_LINUX_BITOPS_H_



#define BITS_PER_LONG         32
#define BITS_PER_BYTE         8

static inline void set_bit(int nr, volatile void *addr)
{
	((unsigned char*)addr)[nr / BITS_PER_BYTE] |= 1UL << (nr % BITS_PER_BYTE);
}

static inline void clear_bit(int nr, volatile void *addr)
{
	((unsigned char*)addr)[nr / BITS_PER_BYTE] &= ~(1UL << (nr % BITS_PER_BYTE));
}

static int test_bit(unsigned int nr, const volatile void *addr)
{
	return ((1UL << (nr % BITS_PER_BYTE)) &
		(((unsigned char*)addr)[nr / BITS_PER_BYTE])) != 0;
}


/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static __always_inline unsigned long __ffs(unsigned long word)
{
	int num = 0;

#if BITS_PER_LONG == 64
	if ((word & 0xffffffff) == 0) {
		num += 32;
		word >>= 32;
	}
#endif
	if ((word & 0xffff) == 0) {
		num += 16;
		word >>= 16;
	}
	if ((word & 0xff) == 0) {
		num += 8;
		word >>= 8;
	}
	if ((word & 0xf) == 0) {
		num += 4;
		word >>= 4;
	}
	if ((word & 0x3) == 0) {
		num += 2;
		word >>= 2;
	}
	if ((word & 0x1) == 0)
		num += 1;
	return num;
}

/*
 * Find the first set bit in a memory region.
 */
static inline unsigned long
find_first_bit(const unsigned long *addr, unsigned long size)
{
	const unsigned long *p = addr;
	unsigned long result = 0;
	unsigned long tmp;

	while (size & ~(BITS_PER_LONG-1)) {
		if ((tmp = *(p++)))
			goto found;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	}
	if (!size)
		return result;

	tmp = (*p) & (~0UL >> (BITS_PER_LONG - size));
	if (tmp == 0UL)		/* Are any bits set? */
		return result + size;	/* Nope. */
found:
	return result + __ffs(tmp);
}



#endif //_THINK_LINUX_BITOPS_H_

