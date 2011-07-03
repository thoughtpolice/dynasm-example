#ifndef _UTIL_MACROS_H_
#define _UTIL_MACROS_H_

//////////////////////////////////////////////////
// Macros that inform or otherwise direct the compiler
#if defined(COMPILER_GNUC) || defined(COMPILER_CLANG)
# define INLINE_ME    __inline__ __attribute__((always_inline))
# define DEPRECATED   __attribute__((deprecated))
# define NOTNULL(...) __attribute__((nonnull(__VA_ARGS__)))
# define NORETURN     __attribute__((noreturn))
# define UNUSED       __attribute__((unused))
# define USED         __attribute__((__used__))
# define PRINTF_FORMAT(...) __attribute__((format (printf, __VA_ARGS__)))
# define MUST_CHECK   __attribute__((warn_unused_result))
# define PACKED       __attribute__((packed))
# define ALIGN(x)     __attribute__((aligned(x)))
# define likely(x)    __builtin_expect(!!(x),1)
# define unlikely(x)  __builtin_expect(!!(x),0)
# define cache_prefetch(...)  __builtin_prefetch(__VA_ARGS__)

// hot/cold are only defined on GCC 4.3 and above
# if defined(COMPILER_GNUC) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 3)
#  define HOT_FUNC  __attribute__((hot))
#  define COLD_FUNC __attribute__((cold))
# else /* COMPILER_GNUC */
#  define HOT_FUNC
#  define COLD_FUNC
# endif /* defined(COMPILER_GNUC) */

#else
# define INLINE_ME 
# define DEPRECATED 
# define NOTNULL(...)
# define NORETURN
# define UNUSED
# define USED
# define PRINTF_FORMAT(...)
# define MUST_CHECK
# define PACKED
# define ALIGN(x)
# define likely(x) (x)
# define unlikely(x) (x)
# define cache_prefetch(...)

# define HOT_FUNC
# define COLD_FUNC
#endif /* defined(COMPILER_GNUC) || defined(COMPILER_CLANG) */

//////////////////////////////////////////////////
// Generally useful macros 

#ifndef CACHE_SIZE
#define CACHE_SIZE 64
#endif /* !CACHE_SIZE */

#define countof(a) (sizeof(a)/sizeof(*(a)))
#define ROUND_TO_CACHE_LINE(x) ((((x)+(CACHE_SIZE-1)) / CACHE_SIZE) * CACHE_SIZE)
#define PACK_CACHELINE PACKED ALIGN(CACHE_SIZE)

#define print_strerr(msg, err) \
  fprintf(stderr, "%s: %s\n", msg, strerror(err))


#endif /* !_UTIL_MACROS_H_ */
