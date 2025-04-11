#include <libriscv.h>
#include <instrs.h>
#include <iostream>

#define B_TYPE_LO ((1U << 11) | (1U << 10) | (1U << 9) | (1U << 8))
#define B_TYPE_HI \
	((1U << 30) | (1U << 29) | (1U << 28) | (1U << 27) | (1U << 26) | (1U << 25))

namespace RISCV {
int DecodeBType(uint32_t ins, DecodedInst* inst) { 
	const InstFmt* mask = &BType;
	inst->opcode = OpcodeMap[ins & 0x7F];
	inst->opcode |= (mask->funct3 & ins) << 8;
	inst->src1 = (mask->rs1 & ins) >> 15;
	inst->src2 = (mask->rs2 & ins) >> 20;
	uint32_t sign = ((ins & (1U << 31)) >> 31);
	inst->imm  = (((ins & (1U << 7)) >> 7) << 11) | // Bit 11 
					(((ins & B_TYPE_LO) >> 8) << 1)  | // Bits 1-4
					(((ins & B_TYPE_HI) >> 25) << 5)  | // Bits 5-10
					(((ins & (1U << 31)) >> 31) << 12); // Bit 12
	
	// Sign extension
	inst->imm = (inst->imm << 20) >> 20;
	std::cout << inst->imm << "\n";
	return 1;
}

int DecodeSType(uint32_t ins, DecodedInst* inst) { 
	return 1; 
}

int DecodeFType(uint32_t ins, DecodedInst* inst) { 
	return 1; 
}

int DecodeUType(uint32_t ins, DecodedInst* inst) { 
	return 1; 
}

int DecodeJType(uint32_t ins, DecodedInst* inst) { 
	return 1; 
}

int DecodeRType(uint32_t ins, DecodedInst* inst) { 
	return 1; 
}

int DecodeIType(uint32_t ins, DecodedInst* inst) { 
	return 1; 
}

}
