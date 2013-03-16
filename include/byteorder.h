#ifndef __THINK__BYTE_ORDER_H__
#define __THINK__BYTE_ORDER_H__

#include "inttypes.h"


namespace THINK {

inline ushort swap_word(ushort x)
{
	return ((((ushort)(x)) & 0xff00) >> 8 | (((ushort)(x)) & 0x00ff) << 8);
}

inline uint swap_long(uint x)
{
	return (((((uint)(x)) & 0xff000000) >> 24) |
	((((uint)(x)) & 0x00ff0000) >> 8) |
	((((uint)(x)) & 0x0000ff00) << 8) |
	((((uint)(x)) & 0x000000ff) << 24)
	);
}

inline uint64 swap_longlong(uint64 x)
{
#ifdef __GNUC__
	return (((((uint64)(x)) & 0xff00000000000000llu) >> 56) |
	((((uint64)(x)) & 0x00ff000000000000llu) >> 40) |
	((((uint64)(x)) & 0x0000ff0000000000llu) >> 24) |
	((((uint64)(x)) & 0x000000ff00000000llu) >> 8) |
	((((uint64)(x)) & 0x00000000ff000000llu) << 8) |
	((((uint64)(x)) & 0x0000000000ff0000llu) << 24) |
	((((uint64)(x)) & 0x000000000000ff00llu) << 40) |
	((((uint64)(x)) & 0x00000000000000ffllu) << 56)
	);
#else
	return (((((uint64)(x)) & 0xff00000000000000) >> 56) |
	((((uint64)(x)) & 0x00ff000000000000) >> 40) |
	((((uint64)(x)) & 0x0000ff0000000000) >> 24) |
	((((uint64)(x)) & 0x000000ff00000000) >> 8) |
	((((uint64)(x)) & 0x00000000ff000000) << 8) |
	((((uint64)(x)) & 0x0000000000ff0000) << 24) |
	((((uint64)(x)) & 0x000000000000ff00) << 40) |
	((((uint64)(x)) & 0x00000000000000ff) << 56)
	);
#endif
}

inline bool is_big_endian(void)
{
    static union {
        uint i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

template <int v>
struct Int2Type
{
	enum {value = v};
};

///////////////////////////////////////////////
//////////  flipToLittle
template <typename T>
inline void flipSelfToLittle(T& x)
{
	x = flipToLittle(x);
}

template <typename T>
inline T flipToLittle(const T x)
{
	return flipToLittle(x, Int2Type<sizeof(T)>());
}

template <typename T>
inline T flipToLittle(const T x, Int2Type<1>)
{
	return x;
}

template <typename T>
inline T flipToLittle(const T x, Int2Type<2>)
{
	return is_big_endian() ? swap_word(x) : x;
}

template <typename T>
inline T flipToLittle(const T x, Int2Type<4>)
{
	return is_big_endian() ? swap_long(x) : x;
}

template <typename T>
inline T flipToLittle(const T x, Int2Type<8>)
{
	return is_big_endian() ? swap_longlong(x) : x;
}

///////////////////////////////////////////////
//////////  flipFromLittle
template <typename T>
inline void flipSelfFromLittle(T& x)
{
	x = flipFromLittle(x);
}

template <typename T>
inline T flipFromLittle(const T x)
{
	return flipFromLittle(x, Int2Type<sizeof(T)>());
}

template <typename T>
inline T flipFromLittle(const T x, Int2Type<1>)
{
	return x;
}

template <typename T>
inline T flipFromLittle(const T x, Int2Type<2>)
{
	return is_big_endian() ? swap_word(x) : x;
}

template <typename T>
inline T flipFromLittle(const T x, Int2Type<4>)
{
	return is_big_endian() ? swap_long(x) : x;
}

template <typename T>
inline T flipFromLittle(const T x, Int2Type<8>)
{
	return is_big_endian() ? swap_longlong(x) : x;
}

///////////////////////////////////////////////
//////////  flipToBig
template <typename T>
inline void flipSelfToBig(T& x)
{
	x = flipToBig(x);
}

template <typename T>
inline T flipToBig(const T x)
{
	return flipToBig(x, Int2Type<sizeof(T)>());
}

template <typename T>
inline T flipToBig(const T x, Int2Type<1>)
{
	return x;
}

template <typename T>
inline T flipToBig(const T x, Int2Type<2>)
{
	return is_big_endian() ? x : swap_word(x);
}

template <typename T>
inline T flipToBig(const T x, Int2Type<4>)
{
	return is_big_endian() ? x : swap_long(x);
}

template <typename T>
inline T flipToBig(const T x, Int2Type<8>)
{
	return is_big_endian() ? x : swap_longlong(x);
}

///////////////////////////////////////////////
//////////  flipFromBig
template <typename T>
inline void flipSelfFromBig(T& x)
{
	x = flipFromBig(x);
}

template <typename T>
inline T flipFromBig(const T x)
{
	return flipFromBig(x, Int2Type<sizeof(T)>());
}

template <typename T>
inline T flipFromBig(const T x, Int2Type<1>)
{
	return x;
}

template <typename T>
inline T flipFromBig(const T x, Int2Type<2>)
{
	return is_big_endian() ? x : swap_word(x);
}

template <typename T>
inline T flipFromBig(const T x, Int2Type<4>)
{
	return is_big_endian() ? x : swap_long(x);
}

template <typename T>
inline T flipFromBig(const T x, Int2Type<8>)
{
	return is_big_endian() ? x : swap_longlong(x);
}

} // namespace


#endif// __THINK__BYTE_ORDER_H__
