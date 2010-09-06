#include <stdint.h>

#include "bc.h"

/* Here we use BcMode + BytecodeDef to define the actual
   instruction encodings of our bytecode */
uint32_t bc_encodings[] = {
  /* Extra #define to append comma for enum so we can reuse BcMode */
#define BcMode1(op, name, p1, p2, p3) BcMode(op,name,p1,p2,p3),
  BytecodeDef(BcMode1)
#undef  BcMode1
};
