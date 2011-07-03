#ifndef _UTIL_TRACE_H_
#define _UTIL_TRACE_H_


static inline void __trace(const char* file, int line, char* prefix, char* fmt, ...) HOT_FUNC PRINTF_FORMAT(4,5); 

#ifdef DEBUG
#define trace(...) __trace(__FILE__, __LINE__, "[T]", __VA_ARGS__)
#define warn(...) __trace(__FILE__, __LINE__, "[W]", __VA_ARGS__)
#define err(...) __trace(__FILE__, __LINE__, "[E]", __VA_ARGS__)
#else /* DEBUG */
#define trace(...) do {} while(false)
#define warn(...) do {} while(false)
#define err(...) do {} while(false)
#endif

#define panic(...) do {					\
    __trace(__FILE__, __LINE__, "[P]", __VA_ARGS__);	\
    exit(-1);						\
} while (false)

static inline void
__trace(const char* file, int line, char* prefix, char* fmt, ...) {
  va_list ap;
  
  va_start(ap,fmt);
  fprintf(stderr, "%s[%s:%d] ", prefix, file, line);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  return;
}

#endif /* !_UTIL_TRACE_H_ */
