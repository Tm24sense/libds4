#pragma once

#include <stdint.h>

/* =======================
   SINGLE BIT MACROS
   ======================= */

// Set a single bit to 1
#define BIT_SET(x, n)       ((x) |= (1U << (n)))

// Clear a single bit to 0
#define BIT_CLEAR(x, n)     ((x) &= ~(1U << (n)))

// Toggle a single bit
#define BIT_TOGGLE(x, n)    ((x) ^= (1U << (n)))

// Check a single bit (returns 0 or 1)
#define BIT_CHECK(x, n)     (((x) >> (n)) & 1U)

/* =======================
   MULTI-BIT / RANGE MACROS
   ======================= */

// Create a mask of width bits starting at position pos
#define BIT_MASK(pos, width) (((1U << (width)) - 1U) << (pos))

// Set multiple bits to 1
#define BIT_SET_RANGE(x, pos, width)     ((x) |= BIT_MASK(pos, width))

// Clear multiple bits to 0
#define BIT_CLEAR_RANGE(x, pos, width)   ((x) &= ~BIT_MASK(pos, width))

// Assign a value to a bit range (overwrites existing bits)
#define BIT_ASSIGN_RANGE(x, pos, width, value) \
    do { \
        (x) &= ~BIT_MASK(pos, width); \
        (x) |= ((value) << (pos)) & BIT_MASK(pos, width); \
    } while(0)

// Get the value of a bit range
#define BIT_GET_RANGE(x, pos, width)  (((x) & BIT_MASK(pos, width)) >> (pos))

/* =======================
   RANGE CHECK MACROS
   ======================= */

// Check if any bit in range is set (returns 1 if any are 1)
#define BIT_ANY_SET(x, pos, width)  (((x) & BIT_MASK(pos, width)) != 0)

// Check if all bits in range are set (returns 1 only if all are 1)
#define BIT_ALL_SET(x, pos, width)  (((x) & BIT_MASK(pos, width)) == BIT_MASK(pos, width))

// Check if no bits in range are set
#define BIT_NONE_SET(x, pos, width) (((x) & BIT_MASK(pos, width)) == 0)

/* =======================
   SHIFT & ROTATE HELPERS
   ======================= */

// Rotate left (circular)
#define ROTL(x, n, bits)   (((x) << (n)) | ((x) >> ((bits) - (n))))

// Rotate right (circular)
#define ROTR(x, n, bits)   (((x) >> (n)) | ((x) << ((bits) - (n))))

/* =======================
   UTILITY MACROS
   ======================= */

// Count number of 1s in a 32-bit value
#define BIT_COUNT_32(x) (__builtin_popcount(x))

// Count number of trailing zeros (gcc/clang)
#define BIT_CTZ_32(x)   (__builtin_ctz(x))

// Count number of leading zeros (gcc/clang)
#define BIT_CLZ_32(x)   (__builtin_clz(x))
