#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

#include "compile.h"
#include "util.h"

int main(int ac, char **av)
{
  BuildCtx ctx_;
  BuildCtx *ctx = &ctx_;
  int ret = 0;

  if((ret = build_code(ctx))) {
    fprintf(stderr,"DynASM error: %08x\n", ret);
  }
  return ret;
}
