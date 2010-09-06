#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>

#include "util.h"

void *pa_malloc(size_t sz, bool is_executable)
{
  int ret = 0;
  void *pret = NULL;
  size_t pagesz = (size_t)sysconf(_SC_PAGESIZE);

  if(pagesz == -1) handle_err("sysconf");
  if((ret = posix_memalign(&pret, pagesz, sz)) != 0) 
    handle_err_code("posix_memalign", ret);

  if(is_executable) {
    if((ret = mprotect(pret,sz,PROT_READ|PROT_WRITE|PROT_EXEC)) != 0)
      handle_err("mprotect");
  }

  return pret;
}
