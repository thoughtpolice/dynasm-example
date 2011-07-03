#include "master.h"

#include "compile.h"
#include "util.h"
#include "bc.h"
#include "vm.h"

int main(int ac, char **av)
{
  int i = 0;
  bc_inst_t program[128] = { 0, };

  program[i++] = enc_bc_SETI(reg(0),imm(10)); /* set r0,10 */
  program[i++] = enc_bc_LBL(lbl(1),nnil);     /* lbl_1: */
  program[i++] = enc_bc_SUBI(reg(0),imm(1));  /*  subi r0,1 */
  program[i++] = enc_bc_LTEI(reg(0),imm(0));  /*  ltei r0,0 */
  program[i++] = enc_bc_BRT(lbl(1),nnil);     /*  brt lbl_1 */
  program[i++] = enc_bc_EXIT(nnil,nnil);      /* exit */

  trace("Running program\n");
  engine(program);

  trace("Compiling code\n");
  Dst_DECL = zcalloc(sizeof(Dst_TYPE));
  build_code(Dst);
  free(Dst);
  return 0;
}
