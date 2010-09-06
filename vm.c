#include <stdio.h>
#include <stdint.h>

#include "bc.h"
#include "vm.h"

int engine(bc_inst_t *ip) {
  void* optable[] = {
#define BcOpTable(op, name, p1, p2, p3) &&l_BC_##name,
      BytecodeDef(BcOpTable)
#undef  BcOpTable
    };

  /* Dispatch first instruction */
  goto *optable[BCIOp(ip[0])];

 l_BC_LT:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_LTI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_GT:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_GTI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_LTE:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_LTEI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_GTE:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_GTEI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_NEG:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_ADD:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_ADDI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_SUB:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_SUBI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_MUL:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_MULI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_DIV:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_DIVI:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_FUNC:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_CALL:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_RET:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_LBL:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_BR:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_BRT:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_BRF:
  printf("got %lu\n", BCIOp(ip[0]));
  goto *optable[BCIOp(++ip[0])];
 l_BC_EXIT:
  printf("got %lu\n", BCIOp(ip[0]));
  printf("finished");

  return 0;
}
