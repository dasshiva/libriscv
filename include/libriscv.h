#ifndef __LIBRISCV_H__
#define __LIBRISCV_H__

#include <cstdint>
#include "opcodes.h"
#include <string>

namespace RISCV {
    struct DecodedInst {
        unsigned opcode;
    };
    
    enum Status {
        SUCCESS = 0,
        INVALID_OPCODE,
        INVALID_INSTRUCTION
    };
    int Decode(uint32_t ins, DecodedInst*);
	std::string ToString(const DecodedInst&);
}
#endif
