#ifndef _BC_H_
#define _BC_H_

#define BC_MAX 255

/* We define the bytecode here using an x-macro basically, only
   slightly different as we don't keep it in a separate file and
   parametrize it by another macro. See BytecodeOp.  For explanation
   of the operand encoding (and '___'), see BytecodeMode. */
#define BytecodeDef(_)				\
  /* Comparison and equality */			\
  _(0,  LT,    reg, reg)			\
  _(1,  LTI,   reg, imm)			\
  _(2,  GT,    reg, reg)			\
  _(3,  GTI,   reg, imm)			\
  _(4,  LTE,   reg, reg)			\
  _(5,  LTEI,  reg, imm)			\
  _(6,  GTE,   reg, reg)			\
  _(7,  GTEI,  reg, imm)			\
  /* Unary operations */			\
  _(8,  NEG,   reg, ___)			\
  /* Binary operations */			\
  _(9,  ADD,   reg, reg)			\
  _(10, ADDI,  reg, imm)			\
  _(11, SUB,   reg, reg)			\
  _(12, SUBI,  reg, imm)			\
  _(13, MUL,   reg, reg)			\
  _(14, MULI,  reg, imm)			\
  _(15, DIV,   reg, reg)			\
  _(16, DIVI,  reg, reg)			\
  /* Call instructions */			\
  _(17, CALL,  label, ___)			\
  _(18, FUNC,  label, ___)			\
  _(19, RET,   ___, ___)			\
  /* Loop instructions */			\
  _(20, LBL,   label, ___)			\
  _(21, BR,    label, ___)			\
  _(22, BRT,   label, ___)			\
  _(23, BRF,   label, ___)			\
  /* Setting register values */			\
  _(24, SETI,  reg, imm)			\
  _(25, SETR,  reg, reg)			\
  /* Exit */					\
  _(26, EXIT,  ___, ___)

/* Definition of bytecode operations */
typedef enum {
#define BcEnum(op, name, p1, p2) BC_##name = op,
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

   LSB                                MSB
   1              8   10   12    14    16
   +------------------------------------+
   |   Opcode     | P1 | P2 |    NIL    |
   +------------------------------------+

  where NIL=BcMode_none
*/

/* Define the bytecode operand table */
#define BcMode(op, name, p1, p2)		\
  ((op)|(BcMode_##p1<<8)|(BcMode_##p2<<10)|(BcMode_none<<12)|(BcMode_none<<14))

/* Convenience macros for extracting operand info from table */
#define BCMOp(x) ((x) & 0xFF)
#define BCMP1(x) (((x) >> 8) & 0x3)
#define BCMP2(x) (((x) >> 10) & 0x3)


/* Now we define the actual encoding of a bytecode instruction itself;
   that is, the instructions given to the virtual machine to trace.

   Format is defined as:
   
   LSB                             MSB
   1        8   16   32     48     64
   +---------------------------------+
   | Opcode |   P1    |     P2       |
   +---------------------------------+

   The N/A field should be set to all 0s.
*/

/* Macros for extracting fields from an instruction.
   Must be kept in alignment with encoder in bc.c!*/
#define BCIOp(x) ((x) & 0xFF)
#define BCIP1(x) ((x>>8) & 0xFFFFFF)
#define BCIP2(x) ((x>>32) & 0xFFFFFFFF)


typedef uint64_t bc_inst_t;  /* Instruction size */
typedef uint32_t bc_param_t; 
/* We say parameters are 32 bits in size but in practice
   only one of them is, the first parameter only uses 24 bits
   and the remaining one uses 32 bits. */

/* Macros for encoding parameters for the encoding functions above. */
#define reg(x) ((x) & 0xFFFFFF) /* Register refs are 24 bits */
#define lbl(x) ((x) & 0xFFFFFF) /* Label refs are 24 bits */
#define imm(x) (x) /* Immediates are 32 bit */
#define nnil   0


/* Here we use BcMode + BytecodeDef to define the operand encoding
   table */
UNUSED static uint16_t bc_encodings[] = {
  /* Extra #define to append comma for enum so we can reuse BcMode */
#define BcMode1(op, name, p1, p2) BcMode(op,name,p1,p2),
  BytecodeDef(BcMode1)
#undef  BcMode1
};

/* Generate functions for encoding values */
#define BcInst(op, name, p1, p2)      \
  static inline \
  bc_inst_t enc_bc_##name(bc_param_t par1, bc_param_t par2) {    \
    bc_inst_t r = 0;          \
    r |= par2; r = r << 24;             \
    r |= par1; r = r << 8;        \
    r |= op;            \
    return r;         \
  }

BytecodeDef(BcInst)
#undef  BcInst


#endif /* _BC_H_ */
