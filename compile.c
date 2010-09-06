#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

#include "util.h"
#include "compile.h"

/* Include our glue macros */
#include "dasm_glue.h" 

/* Prototypes & definitions */
#include "dynasm/dasm_proto.h" 

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

int build_code(Dst_DECL)
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
