#include "types.h"
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

// MurmurHash2, by Austin Appleby
// (public domain, cf. http://murmurhash.googlepages.com/)

uint murmurhash2(const void *key, int len, uint seed)
{
  // 'm' and 'r' are mixing constants generated offline.
  // They're not really 'magic', they just happen to work well.
  const uint m = 0x5bd1e995;
  const int r = 24;

  // Initialize the hash to a 'random' value
  uint h = seed ^ len;

  // Mix 4 bytes at a time into the hash
  const unsigned char *data = static_cast<const unsigned char *>(key);

  while (len >= 4)
  {
    uint k = ((uint)data[0]) | (((uint)data[1])<<8)
                 | (((uint)data[2])<<16) | (((uint)data[3])<<24);

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array
  switch (len)
  {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
            h *= m;
  };

  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.
  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

uint64 murmurhash64A(const void* key, int len, uint64 seed)
{
  const uint64 m = 0xc6a4a7935bd1e995LL;
  const int r = 47;

  uint64 h = seed ^ (len * m);

  const uint64 * data = (const uint64 *)key;
  const uint64 * end = data + (len/8);

  while(data != end)
  {
    uint64 k = *data++;

    k *= m;
    k ^= k >> r;
    k *= m;

    h ^= k;
    h *= m;
  }

  const unsigned char * data2 = (const unsigned char*)data;

  switch(len & 7)
  {
  case 7: h ^= uint64(data2[6]) << 48;
  case 6: h ^= uint64(data2[5]) << 40;
  case 5: h ^= uint64(data2[4]) << 32;
  case 4: h ^= uint64(data2[3]) << 24;
  case 3: h ^= uint64(data2[2]) << 16;
  case 2: h ^= uint64(data2[1]) << 8;
  case 1: h ^= uint64(data2[0]);
          h *= m;
  };

  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
}

uint fnv_hash2(const void *key, int len, uint seed)
{
  const int p = 16777619;
  int hash = (int)2166136261L;
  const char *data = static_cast<const char *>(key);
  for(int i = 0; i < len; i++)
  {
    hash = (hash ^ data[i]) * p;
  }
  hash += hash << 13;
  hash ^= hash >> 7;
  hash += hash << 3;
  hash ^= hash >> 17;
  hash += hash << 5;
  hash ^= seed;
  return hash;
}
