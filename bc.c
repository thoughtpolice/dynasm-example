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
#define BcMode1(op, name, p1, p2) BcMode(op,name,p1,p2),
  BytecodeDef(BcMode1)
#undef  BcMode1
};


/* Generate functions for encoding values */
#define BcInst(op, name, p1, p2)			\
  bc_inst_t enc_bc_##name(bc_param_t par1,		\
			  bc_param_t par2) {		\
    							\
    bc_inst_t r = 0;					\
    r |= par2; r = r << 24;	       			\
    r |= par1; r = r << 8;				\
    r |= op;						\
    return r;					\
  }

BytecodeDef(BcInst)
#undef  BcInst
