#ifndef _BC_H_
#define _BC_H_

#define BC_MAX 255

/* We define the bytecode here using an x-macro basically, only
   slightly different as we don't keep it in a separate file and
   parametrize it by another macro. See BytecodeOp.  For explanation
   of the operand encoding (and '___'), see BytecodeMode. */
#define BytecodeDef(_)				\
  /* Comparison and equality */			\
  _(1,  LT,    reg, reg, ___)			\
  _(2,  LTI,   reg, imm, ___)			\
  _(3,  GT,    reg, reg, ___)			\
  _(4,  GTI,   reg, imm, ___)			\
  _(5,  LTE,   reg, reg, ___)			\
  _(6,  LTEI,  reg, imm, ___)			\
  _(7,  GTE,   reg, reg, ___)			\
  _(8,  GTEI,  reg, imm, ___)			\
  /* Unary operations */			\
  _(9,  NEG,   reg, ___, ___)			\
  /* Binary operations */			\
  _(10, ADD,   reg, reg, ___)			\
  _(11, ADDI,  reg, imm, ___)			\
  _(12, SUB,   reg, reg, ___)			\
  _(13, SUBI,  reg, imm, ___)			\
  _(14, MUL,   reg, reg, ___)			\
  _(15, MULI,  reg, imm, ___)			\
  _(16, DIV,   reg, reg, ___)			\
  _(17, DIVI,  reg, reg, ___)			\
  /* Call instructions */			\
  _(18, CALL, label, ___, ___)			\
  /* Loop instructions */			\
  _(19, BR,   imm, ___, ___)			


/* Definition of bytecode operations */
typedef enum {
#define BcEnum(op, name, p1, p2, p3) BC_##name,
  BytecodeDef(BcEnum)
#undef  BcEnum
} BytecodeOp;


/* Encoding operand modes for bytecode definitions above is using
   another x-macro like trick: we define an enum for the definitions
   of our operands (reg, imm, label etc) and use a macro to expand
   uses of those terms in BCDEF to the below enumeration.  The usage
   of '___' in the operands means nothing and it is #define'd as
   BcMode_none. See below for an example of usage. */
typedef enum {
  BcMode_none, BcMode_reg, BcMode_imm, BcMode_label,
} BytecodeMode;
#define BcMode____ BcMode_none

/* Now we define how we actually encode a bytecode instruction
   in its entirety. The format is:

   LSB                MSB
   1    8   16   24    32
   +--------------------+
   | Op | P1 | P2 | P3  |
   +--------------------+
*/

#define BcMode(op, name, p1, p2, p3)		\
  ((op)|(BcMode_##p1<<8)|(BcMode_##p2<<16)|(BcMode_##p3<<24))

#define BCMOp(x) (x & 0xF)
#define BCMP1(x) BCMOp((x >> 8))
#define BCMP2(x) BCMOp((x >> 16))
#define BCMP3(x) BCMOp((x >> 24))

uint32_t bc_encodings[BC_MAX];
#endif /* _BC_H_ */
