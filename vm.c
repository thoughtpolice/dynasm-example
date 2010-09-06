#include <stdint.h>

#include "bc.h"
#include "vm.h"

int engine(uint32_t *ip) {
  void* optable[] = {
#define BcOpTable(op, name, p1, p2, p3) &&l_BC_##name,
      BytecodeDef(BcOpTable)
#undef  BcOpTable
    };

  /* Dispatch first instruction */
  goto *optable[BCIOp(ip[0])];

 l_BC_LT:
 l_BC_LTI:
 l_BC_GT:
 l_BC_GTI:
 l_BC_LTE:
 l_BC_LTEI:
 l_BC_GTE:
 l_BC_GTEI:
 l_BC_NEG:
 l_BC_ADD:
 l_BC_ADDI:
 l_BC_SUB:
 l_BC_SUBI:
 l_BC_MUL:
 l_BC_MULI:
 l_BC_DIV:
 l_BC_DIVI:
 l_BC_CALL:
 l_BC_RET:
 l_BC_BR:
 l_BC_BRLT:
 l_BC_BRGT:
 l_BC_BRLTE:
 l_BC_BRGTE:

  return 0;
}
