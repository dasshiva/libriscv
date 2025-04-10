#ifndef __INSTR_FORMAT_H__
#define __INSTR_FORMAT_H__

#include "opmap.h"
namespace RISCV {
// Wider types like uint32_t are used explicitly in place of smaller 
// type like uint8_t because modern processors are better at dealing
// with data whose sizes are equal to near their native word size

// We already know the opcode if we came here so no use storing
// it separately inside the struct again

// If any field of InstFmt is initialised to this, it means that the 
// instruction does not use this field. This value is 0 because
// masking with 0 will always produce no values other than 0 avoiding
// weird values coming from malicious instructions
#define NQ_MASK (0U)

/* This struct stores the masks necessary to extract certain fields 
 * of the given instruction. Note that not all may be initialised
 * to a valid mask in this struct as all instructions do not require all fields.
 * The value NQ_MASK is stored in this case to that field indicating
 * that this field is not used by the instruction
 */
struct InstFmt {
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t funct3;
    uint32_t funct7;
    uint32_t imm;
};

// Meaning of numbers used in masks
// <Hex>        <Decimal>    <Binary>
// 0x7C0      = 1984       = 0b11111000000
// 0x7000     = 28672      = 0b11100000000000
// 0xF8000    = 1015808    = 0b1111100000000000
// 0xF00000   = 15728640   = 0b111100000000000000000000
// 0x1F00000  = 32505856   = 0b111110000000000000000
// 0xF000000  = 251658240  = 0b1111000000000000000000000000
// 0xF0000000 = 4026531840 = 0b11110000000000000000000000000000
// 0xFE000000 = 4261412864 = 0b11111110000000000000000000000000
// 0xFFF00000 = 4293918720 = 0b11111111111100000000000000000000
// 0xFFFFF000 = 4294963200 = 0b11111111111111111111000000000000

// All the known instruction formats
static const InstFmt RType = { 0x7C0U, 0xF8000U, 0x1F00000U, 
    0x7000U, 0xFE000000U, NQ_MASK};
static const InstFmt IType = { 0x7C0U, 0XF800U, NQ_MASK, 
    0x7000U, NQ_MASK, 0xFFF00000U};
static const InstFmt SType = { NQ_MASK, 0xF8000U, 0x1F00000U, 
    0x7000U, NQ_MASK, (0x7C0U | 0xFE000000U)};
static const InstFmt BType = { NQ_MASK, 0xF800U, 0x1F00000U, 
    0x7000U, NQ_MASK, (0x7C0U | 0xFE000000U)};
static const InstFmt UType = { 0x7C0U, NQ_MASK, NQ_MASK,
     NQ_MASK, NQ_MASK, 0xFFFFF000U};
static const InstFmt JType = { 0x7C0U, NQ_MASK, NQ_MASK,
     NQ_MASK, NQ_MASK, 0xFFFFF000U};
static const InstFmt FType = { NQ_MASK, NQ_MASK, 0xF0000000U,
     NQ_MASK, 0xF00000U, 0xF000000U};

// For FENCE, we use Rtype but with complications
// funct7 = succ, imm = pred, rs2 = fm
// For B-Type and J-Type, extra work has to be done to get the actual
// value of the immediate

struct DecodedInst;

typedef int (*DecoderFun)(uint32_t, DecodedInst*);
int DecodeBType(uint32_t, DecodedInst*);
int DecodeSType(uint32_t, DecodedInst*);
int DecodeFType(uint32_t, DecodedInst*);
int DecodeUType(uint32_t, DecodedInst*);
int DecodeJType(uint32_t, DecodedInst*);
int DecodeRType(uint32_t, DecodedInst*);
int DecodeIType(uint32_t, DecodedInst*);

// All instruction under the same major opcode have the same format
#if defined(__clang__) || defined(__GNUC__)
static const DecoderFun Decoders[]  = {
    [LOAD] = DecodeIType,
    [MISC_MEM] = DecodeFType,
    [OP_IMM] = DecodeIType,
    [AUIPC] = DecodeUType,
    [OP_IMM32] = DecodeIType,
    [STORE] = DecodeSType,
    [OP] = DecodeRType,
    [LUI] = DecodeUType,
    [OP_32] = DecodeRType,
    [BRANCH] = DecodeBType,
    [JALR] = DecodeIType,
    [JAL] = DecodeJType,
    [SYSTEM] = DecodeIType
};

#else // endif __clang__ || __GNUC__
static const InstFmt* Opc2Fmt[]  = {
    &IType,
    &RType,
    &IType,
    &UType,
    &IType,
    &SType,
    &RType,
    &UType,
    &RType,
    &BType,
    &IType,
    &JType,
    &IType,
};
#endif
}

#endif