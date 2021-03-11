#ifndef x64_REGISTERS_H
#define x64_REGISTERS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
    Contains all supported registers.
    Not supported is:
        -> Segmentation (SS, CS, DS etc..)
        -> MMX (MM0-MM7)
        -> x87 FPU (ST0-ST7)
        -> Debug Registers (DR*)
        -> Control Registers (CR*)
*/
enum ter_x64_register {
    TER_x64_REGISTER_RAX,
    TER_x64_REGISTER_EAX,
    TER_x64_REGISTER_AX,
    TER_x64_REGISTER_AH,
    TER_x64_REGISTER_AL,

    TER_x64_REGISTER_RBX,
    TER_x64_REGISTER_EBX,
    TER_x64_REGISTER_BX,
    TER_x64_REGISTER_BH,
    TER_x64_REGISTER_BL,

    TER_x64_REGISTER_RCX,
    TER_x64_REGISTER_ECX,
    TER_x64_REGISTER_CX,
    TER_x64_REGISTER_CH,
    TER_x64_REGISTER_CL,

    TER_x64_REGISTER_RDX,
    TER_x64_REGISTER_EDX,
    TER_x64_REGISTER_DX,
    TER_x64_REGISTER_DH,
    TER_x64_REGISTER_DL,

    TER_x64_REGISTER_RSI,
    TER_x64_REGISTER_ESI,
    TER_x64_REGISTER_SI,
    TER_x64_REGISTER_SIL,

    TER_x64_REGISTER_RDI,
    TER_x64_REGISTER_EDI,
    TER_x64_REGISTER_DI,
    TER_x64_REGISTER_DIL,

    TER_x64_REGISTER_RBP,
    TER_x64_REGISTER_EBP,
    TER_x64_REGISTER_BP,
    TER_x64_REGISTER_BPL,

    TER_x64_REGISTER_RSP,
    TER_x64_REGISTER_ESP,
    TER_x64_REGISTER_SP,
    TER_x64_REGISTER_SPL,

    TER_x64_REGISTER_RIP,
    TER_x64_REGISTER_EIP,
    TER_x64_REGISTER_IP,

    TER_x64_REGISTER_R8,
    TER_x64_REGISTER_R8D,
    TER_x64_REGISTER_R8W,
    TER_x64_REGISTER_R8B,

    TER_x64_REGISTER_R9,
    TER_x64_REGISTER_R9D,
    TER_x64_REGISTER_R9W,
    TER_x64_REGISTER_R9B,

    TER_x64_REGISTER_R10,
    TER_x64_REGISTER_R10D,
    TER_x64_REGISTER_R10W,
    TER_x64_REGISTER_R10B,

    TER_x64_REGISTER_R11,
    TER_x64_REGISTER_R11D,
    TER_x64_REGISTER_R11W,
    TER_x64_REGISTER_R11B,

    TER_x64_REGISTER_R12,
    TER_x64_REGISTER_R12D,
    TER_x64_REGISTER_R12W,
    TER_x64_REGISTER_R12B,

    TER_x64_REGISTER_R13,
    TER_x64_REGISTER_R13D,
    TER_x64_REGISTER_R13W,
    TER_x64_REGISTER_R13B,

    TER_x64_REGISTER_R14,
    TER_x64_REGISTER_R14D,
    TER_x64_REGISTER_R14W,
    TER_x64_REGISTER_R14B,

    TER_x64_REGISTER_R15,
    TER_x64_REGISTER_R15D,
    TER_x64_REGISTER_R15W,
    TER_x64_REGISTER_R15B,

    TER_x64_REGISTER_COUNT
};

extern bool ter_x64_is_accumulator(const enum ter_x64_register reg);
extern bool ter_x64_is_high_byte(const enum ter_x64_register reg);
extern bool ter_x64_uniform_byte(const enum ter_x64_register reg);
extern bool ter_x64_is_extended(const enum ter_x64_register reg);

extern const uint8_t TER_X64_REGISTER_ID_TABLE[TER_x64_REGISTER_COUNT];
extern const uint8_t TER_X64_REGISTER_SIZE_TABLE[TER_x64_REGISTER_COUNT];
extern const char* const TER_X64_REGISTER_MNEMONICS[TER_x64_REGISTER_COUNT];

#ifdef __cplusplus
}
#endif

#endif
