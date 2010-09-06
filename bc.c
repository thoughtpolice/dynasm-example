#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "bc.h"

/* Here we use BcMode + BytecodeDef to define the operand encoding
   table */
uint16_t bc_encodings[] = {
  /* Extra #define to append comma for enum so we can reuse BcMode */
#define BcMode1(op, name, p1, p2, p3) BcMode(op,name,p1,p2,p3),
  BytecodeDef(BcMode1)
#undef  BcMode1
};


/* Generate functions for encoding values */
#define BcInst(op, name, p1, p2, p3)			\
  bc_inst_t bc_enc_inst_##name() {			\
    return 0;						\
  }

BytecodeDef(BcInst)
#undef  BcInst
