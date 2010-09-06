#ifndef _COMPILE_H_
#define _COMPILE_H_

typedef struct {
  struct dasm_State *D;
} BuildCtx;

typedef int (*dasm_gen_func)();

/* General definitions */
#define GLOB_MAX 1024


int build_code(BuildCtx *ctx);

#endif /* _COMPILE_H_ */
