#include <libriscv.h>
#include <instrs.h>

namespace RISCV {
int DecodeBType(uint32_t ins, DecodedInst* inst) { return 1; }
int DecodeSType(uint32_t ins, DecodedInst* inst) { return 1; }
int DecodeFType(uint32_t ins, DecodedInst* inst) { return 1; }
int DecodeUType(uint32_t ins, DecodedInst* inst) { return 1; }
int DecodeJType(uint32_t ins, DecodedInst* inst) { return 1; }
int DecodeRType(uint32_t ins, DecodedInst* inst) { return 1; }
int DecodeIType(uint32_t ins, DecodedInst* inst) { return 1; }
}