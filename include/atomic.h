#ifndef _THINK_ATOMIC_H_
#define _THINK_ATOMIC_H_

namespace THINK{
          
inline long atomic_add(long volatile* pw, long dv)
{
	// *pw += dv;
    // return *pw;

    int r;

    __asm__ __volatile__
    (
        "lock\n\t"
        "xadd %1, %0":
        "=m"( *pw ), "=r"( r ): // outputs (%0, %1)
        "m"( *pw ), "1"( dv ): // inputs (%2, %3 == %1)
        "memory", "cc" // clobbers
    );

    return r + dv;
}

/// set value, return old val
inline long atomic_xchg(long volatile* target, long value)
{
	// code from ace
	unsigned long addr = reinterpret_cast<unsigned long> (target);
	// The XCHG instruction automatically follows LOCK semantics
	__asm__ __volatile__( "xchg %0, (%1)" : "+r"(value) : "r"(addr) );
	return value;
}

/// compare, if equal, set value, always return old val
inline long atomic_cmp_xchg(long volatile* dst, long xchg, long cmp)
{
	int r;

	__asm__ __volatile__
	(
		"lock; cmpxchgl %1, %2"
		: "=a" (r)
		: "r" (xchg), "m" (*dst), "0"(cmp)
		: "memory", "cc"
	);
	return r;
}
} //end of namespace
#endif //_THINK_ATOMIC_H_
