/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 * Version: $Id$
 *
 * Authors:
 *   yangjh <yjhjstz@163.com>
 *
 */
#ifndef _THINK_TYPES_DEFINE_
#define _THINK_TYPES_DEFINE_

#include <stdio.h>
#include <string>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
// base types definition
typedef signed char				schar;	///< sizeof(uchar) == sizeof(schar) == sizeof(char) == 1
typedef unsigned char			uchar;	
typedef unsigned int			uint;	///< sizeof(uint) == sizeof(int) == 4
typedef unsigned short			ushort;	///< sizeof(ushort) == sizeof(short) == 2
typedef unsigned long			ulong;	///< sizeof(ulong) == sizeof(long) == 4
#ifdef WIN32
typedef __int64					int64;	///< sizeof(int64) == sizeof(uint64) == 8
typedef unsigned __int64		uint64;
#elif defined(__GNUC__)
typedef long long				int64;
typedef unsigned long long		uint64;
#elif defined(__TCS__)
typedef signed   long long int	int64;
typedef unsigned long long int	uint64;
#endif


//some useful  micros
typedef int         BOOL;
#define FALSE       0
#define TRUE        1

#define FAILURE     (-1)
#define SUCCESS     0

#ifdef _DEBUG
#define DEBUG_PRINT(...) printf("FILE:%20s, LINE:%5d\n",__FILE__,__LINE__) ;printf(__VA_ARGS__);
#else
#define DEBUG_PRINT(...)
#endif
#ifndef NULL
#define NULL                ((void *)0)
#endif

#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

#define ARRAYSIZEOF(a) (sizeof(a)/sizeof(a[0]))


#endif //_THINK_TYPES_DEFINE_
