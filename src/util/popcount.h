#ifndef _UTIL_POPCOUNT_H_
#define _UTIL_POPCOUNT_H_

#define SSE_POPCNT

#define __native_popcnt32(_v) ({\
      typeof(_v) v = _v;\
      v = v - ((v >> 1) & 0x55555555);\
      v = (v & 0x33333333) + ((v >> 2) & 0x33333333);\
      (typeof(_v))(((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24);\
    })

#define __native_popcnt64(_w) ({\
      typeof(_w) w = _w;\
      typeof(_w) w1 = (w & 0x2222222222222222) + ((w+w) & 0x2222222222222222); \
      typeof(_w) w2 = (w >> 1 & 0x2222222222222222) + (w >> 2 & 0x2222222222222222); \
      w1 = w1 + (w1 >> 4) & 0x0f0f0f0f0f0f0f0f;\
      w2 = w2 + (w2 >> 4) & 0x0f0f0f0f0f0f0f0f;\
      (typeof(_w))((w1 + w2) * 0x0101010101010101 >> 57);\
    })


#define __native_popcnt(x) (sizeof(typeof(x)) <= sizeof(uint32_t) ?\
			    __native_popcnt32((uint32_t)(x)) : __native_popcnt64(x))

/*
#define __native_popcnt(x) 				\
  choose_expr(types_compatible(typeof(x), uint64_t),    \
    __native_popcnt64(x),                               \
    choose_expr(types_compatible(typeof(x), uint32_t),  \
	        __native_popcnt32(x),                   \
	        (void)0))                               
*/

#define __sse4_popcnt(x) ({\
      typeof(x) _r = 0;\
      typeof(x) _x = x;\
      __asm__ __volatile__ ("popcnt %1, %0" : "=r" (_r) : "r" (_x));\
      _r;\
    })

#ifdef SSE_POPCNT
#define __popcnt __sse4_popcnt
#else  /* !SSE_POPCNT */
#define __popcnt __native_popcnt
#endif /* SSE_POPCNT */

/*
 * If the parameter is constant, use the native version as constant
 * folding should happen, resulting in a constant value - if we use
 * __popcnt, it may shell out to SSE4.2 'popcnt', and the compiler
 * can't eliminate that.  Clang doesn't seem to support
 * __builtin_constant_p, so it will always fall back onto
 * __popcnt. GCC does, and in the case we don't use SSE4.2 popcnt and
 * it's not constant, it seems to be able to unpack the operations
 * above into nice SSE code, while clang doesn't. Further investigation
 * is needed.
 */
#define popcount(x) (__builtin_constant_p(x) ? __native_popcnt(x) : __popcnt(x))

#endif /* !_UTIL_POPCOUNT_H_ */
