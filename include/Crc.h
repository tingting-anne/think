/*
 * crc32.h
 * See linux/lib/crc32.c for license and changes
 */
#ifndef __THINK_CRC_ORDER_H__
#define __THINK_CRC_ORDER_H__

#include <stddef.h>
#include "types.h"


namespace THINK {



///	crc16 - compute the CRC-16 for the data buffer
///	\param [in] crc: previous CRC value
///	\param [in] buffer: data pointer
///	\param [in] len: number of bytes in the buffer
///
///	\return: The updated CRC value.
///
ushort crc16(ushort crc, uchar const* buffer, uint length);

///	crc32 - compute the CRC-32 for the data buffer
///	\param [in] buffer: data pointer
///	\param [in] len: number of bytes in the buffer
///
///	\return: The updated CRC value.
///
uint crc32 (uchar const* buffer, uint length);


} // namespace


#endif// __THINK_CRC_ORDER_H__


