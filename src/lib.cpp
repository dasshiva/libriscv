#include <libriscv.h>
#include <instrs.h>

namespace RISCV {
    __attribute__((visibility("default")))
    int Decode(uint32_t ins) {
        // Safe to index with ins & 0x7F with no validation because
        // for all values of ins: 0 <= (ins & 0x7F) <= 127
        unsigned op = OpcodeMap[ins & 0x7F];
        if (op == UNDEF_OPCODE)
            return RISCV::INVALID_OPCODE;

        DecodedInst di;
        if (Decoders[op](ins, &di) < 0) 
            return RISCV::INVALID_INSTRUCTION;
        
        return RISCV::SUCCESS;
    }
}