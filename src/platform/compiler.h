#ifndef _PLATFORM_COMPILER_H_
#define _PLATFORM_COMPILER_H_

//////////////////////////////////////////////////////////
// Determine our compiler and give us some info about it
#if    defined(__GNUC__) && !defined(__clang__) // GCC - explicitly make sure clang isn't tricking us
# define COMPILER_GNUC
# define COMPILER_NAME   "GCC"
# define COMPILER_STRING "GCC " __VERSION__

#elif  defined(__clang__)                       // Clang
# define COMPILER_CLANG
# define COMPILER_NAME   "clang"
# define COMPILER_STRING "clang " __VERSION__

#elif  defined(_MSC_VER)                        // MSVC
# define COMPILER_MSVC
# define COMPILER_NAME "MSVC"
# define COMPILER_STRING "MSVC"

#else
# define COMPILER_UNKNOWN
# define COMPILER_NAME   "Unknown"
# define COMPILER_STRING "Unknown"
#endif /* defined(COMPILER) */

#endif /* _PLATFORM_COMPILER_H_ */
