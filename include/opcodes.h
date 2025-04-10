#ifndef __OPCODES_H__
#define __OPCODES_H__

// Definitions copy-pasted from opmap.h
// opmap.h itself is internal only and has symbols that we cannot allow
// users to include in their code, leaving us no choice but to duplicate
// the code

#define UNDEF_OPCODE    (0xFFFFFFFFU)
#define OP_LOAD         (0U)
#define OP_MISC_MEM     (1U)
#define OP_IMM          (2U)
#define OP_AUIPC        (3U)
#define OP_IMM32        (4U)
#define OP_STORE        (5U)
#define OP              (6U)
#define OP_LUI          (7U)
#define OP_32           (8U)
#define OP_BRANCH       (9U)
#define OP_JALR         (0xAU)
#define OP_JAL          (0xBU)
#define OP_SYSTEM       (0xCU)

// Defined values of funct3 we know about
#define F_BEQ  (0U)
#define F_BNE  (1U)
#define F_BLT  (4U) 
#define F_BGE  (5U)
#define F_BLTU (6U)
#define F_BGEU (7U)

namespace RISCV {
enum Opcode {
	LUI   =  OP_LUI,
	JAL   =  OP_JAL,
	JALR  =  OP_JALR,
	AUIPC =  OP_AUIPC,
	BEQ   =  (OP_BRANCH) | (F_BEQ << 8),
	BNE   =  (OP_BRANCH) | (F_BNE << 8),
	BLT   =  (OP_BRANCH) | (F_BLT << 8),
	BGE   =  (OP_BRANCH) | (F_BGE << 8),
	BLTU  =  (OP_BRANCH) | (F_BLTU << 8),
	BGEU  =  (OP_BRANCH) | (F_BGEU << 8),
};
}

#endif
