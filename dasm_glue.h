#ifndef _DASM_GLUE_H_
#define _DASM_GLUE_H_

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

#endif /* _DASM_GLUE_H_ */
