#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

#include <sys/mman.h>

#include "util.h"

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

/* Include our glue macros */
#include "dasm_glue.h" 

/* Include DynASM implementation */
#include "dynasm/dasm_x86.h"

/* Include our code generator */
#include "backend.h"


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
  code = (uint8_t *)pa_malloc(codesz, true);
  if((ret = dasm_encode(Dst, (void *)code))) return ret;

  write_raw("debug.out", code, codesz);

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
