#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

#include "util.h"
#include "bc.h"
#include "vm.h"


int main(int ac, char **av)
{
  int i = 0;
  bc_inst_t program[128] = { 0, };

  program[i++] = enc_bc_ADD(1,2,3);
  program[i++] = enc_bc_CALL(1,2,3);
  program[i++] = enc_bc_BR(1,2,3);
  program[i++] = enc_bc_EXIT(1,2,3);

  engine(program);
  return 0;
}
