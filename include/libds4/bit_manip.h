#pragma once

#include <stdint.h>

#define BIT_SET(x, n) ((x) |= (1U << (n)))

#define BIT_CLEAR(x, n) ((x) &= ~(1U << (n)))

#define BIT_TOGGLE(x, n) ((x) ^= (1U << (n)))

#define BIT_CHECK(x, n) (((x) >> (n)) & 1U)

#define BIT_MASK(pos, width) (((1U << (width)) - 1U) << (pos))

#define BIT_SET_RANGE(x, pos, width) ((x) |= BIT_MASK(pos, width))

#define BIT_CLEAR_RANGE(x, pos, width) ((x) &= ~BIT_MASK(pos, width))

#define BIT_ASSIGN_RANGE(x, pos, width, value)          \
   do                                                   \
   {                                                    \
      (x) &= ~BIT_MASK(pos, width);                     \
      (x) |= ((value) << (pos)) & BIT_MASK(pos, width); \
   } while (0)

#define BIT_GET_RANGE(x, pos, width) (((x) & BIT_MASK(pos, width)) >> (pos))

#define BIT_ANY_SET(x, pos, width) (((x) & BIT_MASK(pos, width)) != 0)

#define BIT_ALL_SET(x, pos, width) (((x) & BIT_MASK(pos, width)) == BIT_MASK(pos, width))

#define BIT_NONE_SET(x, pos, width) (((x) & BIT_MASK(pos, width)) == 0)

#define ROTL(x, n, bits) (((x) << (n)) | ((x) >> ((bits) - (n))))

#define ROTR(x, n, bits) (((x) >> (n)) | ((x) << ((bits) - (n))))

#define BIT_COUNT_32(x) (__builtin_popcount(x))

#define BIT_CTZ_32(x) (__builtin_ctz(x))

#define BIT_CLZ_32(x) (__builtin_clz(x))
