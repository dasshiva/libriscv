#include <libriscv.h>
#include <instrs.h>

namespace RISCV {
    __attribute__((visibility("default")))
    int Decode(uint32_t ins, DecodedInst* inst) {
        // Safe to index with ins & 0x7F with no validation because
        // for all values of ins: 0 <= (ins & 0x7F) <= 127
        unsigned op = OpcodeMap[ins & 0x7F];
        if (op == UNDEF_OPCODE)
            return RISCV::INVALID_OPCODE;

        if (Decoders[op](ins, inst) < 0) 
            return RISCV::INVALID_INSTRUCTION;

        return RISCV::SUCCESS;
    }

	__attribute__((visibility("default")))
	std::string ToString(const DecodedInst& inst) {
		std::string ret;
		switch (inst.opcode) {
			case Opcode::BEQ: ret += "beq"; break;
			case Opcode::BNE: ret += "bne"; break;
			case Opcode::BLT: ret += "blt"; break;
			case Opcode::BGE: ret += "bge"; break;
			case Opcode::BLTU: ret += "bltu"; break;
			case Opcode::BGEU: ret += "bgeu"; break;
			default: ret += "Unimplemented!";
		}

		return ret;
	}
}
