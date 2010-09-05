#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

typedef struct {
  struct dasm_State *D;
} BuildCtx;

typedef int (*dasm_gen_func)();

/* General definitions */
#define GLOB_MAX 1024
#define DASM_MAXSECTION 1024
#define DASM_ALIGNED_WRITES 1 /* aligned writing */
#ifdef DEBUG
#define DASM_CHECKS 1         /* sanity checks */
#endif

/* DynASM glue definitions */
#define Dst      ctx
#define Dst_DECL BuildCtx *ctx
#define Dst_REF  (ctx->D)

#include "dynasm/dasm_proto.h" /* prototypes */

/* DynASM glue macros */
#define DASM_M_GROW(ctx, t, p, sz, need) \
  do { \
    size_t _sz = (sz), _need = (need); \
    if (_sz < _need) { \
      if (_sz < 16) _sz = 16; \
      while (_sz < _need) _sz += _sz; \
      (p) = (t *)realloc((p), _sz); \
      if ((p) == NULL) exit(1); \
      (sz) = _sz; \
    } \
  } while(0)

#define DASM_M_FREE(ctx, p, size) free(p)

/* Include DynASM implementation */
#include "dynasm/dasm_x86.h"

/* Include our backend */
#include "backend.h"


/* General macros */
#define handle_err(msg) \
  do { perror(msg); exit(1); } while(0)

static void write_raw(const char *file, uint8_t *ptr, size_t sz)
{
  FILE* fp = fopen(file, "w");
  if(fp == NULL) {
    handle_err("fopen");
  }

  if(fwrite(ptr, 1, sz, fp) != sz) {
    handle_err("fwrite");
  }

  fclose(fp);
}

void* page_aligned_malloc(size_t sz)
{
  void* ret = NULL;
  size_t pagesz = (size_t)sysconf(_SC_PAGESIZE);
  
  if(0 != posix_memalign(&ret, pagesz, sz)) {
    handle_err("posix_memalign");
  }

  return ret;
}

static int build_code(Dst_DECL)
{
  int ret = 0;
  size_t codesz = 0;
  uint8_t* code = NULL;

  int nglob = GLOB_MAX;
  void **glob = (void **)malloc(nglob*sizeof(void *));
  memset(glob, 0, nglob*sizeof(void *));

  dasm_init(Dst, DASM_MAXSECTION);
  dasm_setupglobal(Dst, glob, nglob);
  dasm_setup(Dst, build_actionlist);

  (void)create_backend(Dst);

  /* Finalize */
  (void)dasm_checkstep(Dst, -1); /* sanity check */
  if((ret = dasm_link(Dst, &codesz))) return ret;
  code = (uint8_t *)page_aligned_malloc(codesz);
  if((ret = dasm_encode(Dst, (void *)code))) return ret;

#ifdef DEBUG
  write_raw("debug.out", code, codesz);
#endif

  if(0 != mprotect(code, codesz, PROT_EXEC|PROT_READ|PROT_WRITE)) {
    handle_err("mprotect");
  }

  dasm_gen_func fp = (dasm_gen_func)code;
  ret = fp();

  printf("generated function return value = %d\n",ret);

  dasm_free(Dst);
  free(glob);
  free(code);
  return 0;
}

int main(int ac, char **av)
{
  BuildCtx ctx_;
  BuildCtx *ctx = &ctx_;
  int ret = 0;

  if((ret = build_code(ctx))) {
    fprintf(stderr,"DynASM error: %08x\n", ret);
    return 1;
  }

  return 0;
}
