#ifndef _BC_H_
#define _BC_H_

#define BC_MAX 255

/* We define the bytecode here using an x-macro basically, only
   slightly different as we don't keep it in a separate file and
   parametrize it by another macro. See BytecodeOp.  For explanation
   of the operand encoding (and '___'), see BytecodeMode. */
#define BytecodeDef(_)				\
  /* Comparison and equality */			\
  _(0,  LT,    reg, reg, ___)			\
  _(1,  LTI,   reg, imm, ___)			\
  _(2,  GT,    reg, reg, ___)			\
  _(3,  GTI,   reg, imm, ___)			\
  _(4,  LTE,   reg, reg, ___)			\
  _(5,  LTEI,  reg, imm, ___)			\
  _(6,  GTE,   reg, reg, ___)			\
  _(7,  GTEI,  reg, imm, ___)			\
  /* Unary operations */			\
  _(8,  NEG,   reg, ___, ___)			\
  /* Binary operations */			\
  _(9,  ADD,   reg, reg, ___)			\
  _(10, ADDI,  reg, imm, ___)			\
  _(11, SUB,   reg, reg, ___)			\
  _(12, SUBI,  reg, imm, ___)			\
  _(13, MUL,   reg, reg, ___)			\
  _(14, MULI,  reg, imm, ___)			\
  _(15, DIV,   reg, reg, ___)			\
  _(16, DIVI,  reg, reg, ___)			\
  /* Call instructions */			\
  _(17, CALL,  label, ___, ___)			\
  _(18, FUNC,  label, ___, ___)			\
  _(19, RET,   ___, ___, ___)			\
  /* Loop instructions */			\
  _(20, LBL,   label, ___, ___)			\
  _(21, BR,    label, ___, ___)			\
  _(22, BRT,   label, ___, ___)			\
  _(23, BRF,   label, ___, ___)

/* Definition of bytecode operations */
typedef enum {
#define BcEnum(op, name, p1, p2, p3) BC_##name = op,
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
  BcMode_none,
  BcMode_reg,
  BcMode_imm,
  BcMode_label,
} BytecodeMode;
#define BcMode____ BcMode_none

/* Now we define how we encode bytecode operand information.
   This is defined in bc.c as bc_encodings.

   LSB                             MSB
   1              8   10   12   14  16
   +---------------------------------+
   |   Opcode     | P1 | P2 | P3 |NIL|
   +---------------------------------+

  where NIL=BcMode_none
*/

/* BcMode is used in conjunction with BytecodeDef to generate the
   bytecode operand info table. See bc.c. */
#define BcMode(op, name, p1, p2, p3)		\
  ((op)|(BcMode_##p1<<8)|(BcMode_##p2<<10)|(BcMode_##p3<<12)|(BcMode_none<<14))

/* Convenience macros for extracting operand info from table */
#define BCMOp(x) ((x) & 0xFF)
#define BCMP1(x) (((x) >> 8) & 0x3)
#define BCMP2(x) (((x) >> 10) & 0x3)
#define BCMP3(x) (((x) >> 12) & 0x3)

/* The operand info table */
uint16_t bc_encodings[BC_MAX];


/* Now we define the actual encoding of a bytecode instruction itself;
   that is, the instructions given to the virtual machine to trace.

   Format is defined as:
   
   LSB                                MSB
   1        8     16     32     48     64
   +------------------------------------+
   | Opcode | N/A  | P1   | P2   | P3   |
   +------------------------------------+

   The N/A field should be set to all 0s.
*/

typedef uint64_t bc_inst_t;  /* Instruction size */
typedef uint16_t bc_param_t; /* The three parameters are 16-bit */

/* Now we generate some prototypes for functions to help us encode
   instructions in an easy way. Defined in bc.c, look at the BcInst
   macro. */
#define BcInst(op, name, p1, p2, p3)		\
  bc_inst_t enc_bc_##name(bc_param_t, bc_param_t, bc_param_t);
BytecodeDef(BcInst)
#undef  BcInst


/* Macros for extracting fields from an instruction */
#define BCIOp(x) ((x) & 0xFF)
#define BCIP1(x) ((x>>16) & 0xFFFF)
#define BCIP2(x) ((x>>32) & 0xFFFF)
#define BCIP3(x) ((x>>48) & 0xFFFF)

#endif /* _BC_H_ */
