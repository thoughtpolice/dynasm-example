#ifndef _UTIL_H_
#define _UTIL_H_

/* General macros */
#define handle_err(msg) \
  do { perror(msg); exit(1); } while(0)

#define handle_err_code(msg, err)		   \
  do {						   \
  fprintf(stderr, "%s: %s\n", msg, strerror(err)); \
  exit(1);					   \
  } while (0)

/* Allocate memory on a page-aligned boundary */
void *pa_malloc(size_t sz, bool is_executable);

#endif /* _UTIL_H_ */
