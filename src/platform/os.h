#ifndef _PLATFORM_OS_H_
#define _PLATFORM_OS_H_

#if defined(__APPLE__)
 #define PLATFORM_DARWIN
 #define PLATFORM_STRING "Darwin"

#elif defined(__unix__) || defined(unix)
 #define PLATFORM_UNIX
 #define PLATFORM_STRING "Unix"

#elif defined(_WIN32) || defined(_WIN64)
 #define PLATFORM_WINDOWS
 #define PLATFORM_STRING "Windows"

#else
 #define PLATFORM_UNKNOWN
 #define PLATFORM_STRING "Unknown"
#endif /* defined(PLATFORM) */

#endif /* _PLATFORM_OS_H_ */
