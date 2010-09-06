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
  bc_inst_t enc_bc_##name(bc_param_t par1,		\
			  bc_param_t par2,		\
			  bc_param_t par3) {		\
    							\
    bc_inst_t r;					\
    r |= par3; r = r << 16;	      			\
    r |= par2; r = r << 16;	       			\
    r |= par1; r = r << 32;				\
    r |= op;						\
    return r;					\
  }

BytecodeDef(BcInst)
#undef  BcInst
