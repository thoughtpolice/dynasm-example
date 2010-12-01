#include <stdio.h>
#include <stdint.h>

#include "bc.h"
#include "vm.h"

int engine(bc_inst_t *ip) {
  void* optable[] = {
#define BcOpTable(op, name, p1, p2) &&l_BC_##name,
      BytecodeDef(BcOpTable)
#undef  BcOpTable
    };

  /* Dispatch first instruction */
  goto *optable[BCIOp(ip[0])];

 l_BC_LT:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_LTI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_GT:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_GTI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_LTE:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_LTEI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_GTE:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_GTEI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_NEG:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_ADD:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_ADDI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_SUB:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_SUBI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_MUL:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_MULI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_DIV:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_DIVI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_FUNC:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_CALL:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_RET:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_LBL:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_BR:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_BRT:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_BRF:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_SETI:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_SETR:
  printf("got %llu\n", BCIOp(ip[0]));
  goto *optable[BCIOp((++ip)[0])];

 l_BC_EXIT:
  printf("got %llu\n", BCIOp(ip[0]));
  printf("finished\n");

  return 0;
}
