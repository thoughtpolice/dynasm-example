#ifndef _COMPILE_H_
#define _COMPILE_H_

/* Encoder state for compiled code */
typedef struct {
  struct dasm_State *D; /* Internal DynASM state */
} BuildCtx;

/* General DynASM definitions */
#define GLOB_MAX 1024
#define DASM_MAXSECTION 1024
#define DASM_ALIGNED_WRITES 1 /* aligned writing */
#ifdef DEBUG
#define DASM_CHECKS 1         /* sanity checks */
#endif

/* DynASM glue definitions that tie the prototypes for DynASM to BuildCtx above */
#define Dst_TYPE BuildCtx /* Not needed by DynASM, but used by moi */
#define Dst      ctx
#define Dst_DECL Dst_TYPE *ctx
#define Dst_REF  (ctx->D)

typedef int (*dasm_gen_func)();

int build_code(Dst_DECL);

#endif /* _COMPILE_H_ */
