#ifndef _UTIL_ALLOC_H_
#define _UTIL_ALLOC_H_

static inline void*
zmalloc(size_t size)
{
  void *p = NULL;
  
  assert(size > 0);
  
  p = malloc(size);
  if (unlikely(p == NULL))
    panic("could not allocate memory\n");
  
  return p;
}

static inline void*
zcalloc(size_t size)
{
  void *p = NULL;
  
  p = zmalloc(size);
  memset(p,0,size);
  return p;
}

static inline void*
pa_malloc(size_t sz, bool is_executable)
{
  int ret = 0;
  void *pret = NULL;
  size_t pagesz = (size_t)sysconf(_SC_PAGESIZE);

  if(unlikely(pagesz == -1)) {
    panic("sysconf failed: %s\n", strerror(errno));
  }

  ret = posix_memalign(&pret, pagesz, sz);
  if(unlikely(ret != 0)) {
    panic("posix_memalign failed: %s\n", strerror(ret));
  }

  if(is_executable) {
    ret = mprotect(pret,sz,PROT_READ|PROT_WRITE|PROT_EXEC);
    if(unlikely(ret != 0)) {
      panic("mprotect failed: %s\n", strerror(ret));
    }
  }

  return pret;
}

#endif /* !_UTIL_ALLOC_H_ */
