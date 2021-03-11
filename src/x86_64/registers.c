#include "registers.h"

bool ter_x64_register_is_accumulator(const enum ter_x64_register_t reg) {
	return reg == TER_x64_REGISTER_AL || reg == TER_x64_REGISTER_AX || reg == TER_x64_REGISTER_EAX || reg == TER_x64_REGISTER_RAX;
}

bool ter_x64_register_is_high_byte(const enum ter_x64_register_t reg) {
	return reg == TER_x64_REGISTER_AH || reg == TER_x64_REGISTER_BH || reg == TER_x64_REGISTER_CH || reg == TER_x64_REGISTER_DH;
}

bool ter_x64_register_is_uniform_byte(const enum ter_x64_register_t reg) {
	return reg == TER_x64_REGISTER_SIL || reg == TER_x64_REGISTER_DIL || reg == TER_x64_REGISTER_SPL || reg == TER_x64_REGISTER_BPL;
}

bool ter_x64_register_is_extended(const enum ter_x64_register_t reg) {
	return reg >= TER_x64_REGISTER_R8 && reg <= TER_x64_REGISTER_R15B;
}

const uint8_t TER_X64_REGISTER_ID_TABLE[TER_x64_REGISTER_COUNT] = {
	0x00, 0x00, 0x00, 0x04, 0x00, // RAX, EAX, AX, AH, AL
	0x03, 0x03, 0x03, 0x07, 0x03, // RBX, EBX, BX, BH, BL
	0x01, 0x01, 0x01, 0x05, 0x01, // RCX, ECX, CX, CH, CL
	0x02, 0x02, 0x02, 0x06, 0x02, // RDX, EDX, DX, DH, DL
	0x06, 0x06, 0x06, 0x06,       // RSI, ESI, SI, SIL
	0x07, 0x07, 0x07, 0x07,       // RDI, ESI, DI, DIL
	0x05, 0x05, 0x05, 0x05,       // RBP, EBP, BP, BPL
	0x04, 0x04, 0x04, 0x04,       // RSP, ESP, SP, SPL
	0xFF, 0xFF, 0xFF,             // RIP, EIP, IP
	0x00, 0x00, 0x00, 0x00,       // R8, R8D, R8W, R8B
	0x01, 0x01, 0x01, 0x01,       // R9, R9D, R9W, R9B
	0x02, 0x02, 0x02, 0x02,       // R10, R10D, R10W, R10B
	0x03, 0x03, 0x03, 0x03,       // R11, R11D, R11W, R11B
	0x04, 0x04, 0x04, 0x04,       // R12, R12D, R12W, R12B
	0x05, 0x05, 0x05, 0x05,       // R13, R13D, R13W, R13B
	0x06, 0x06, 0x06, 0x06,       // R14, R14D, R14W, R14B
	0x07, 0x07, 0x07, 0x07,       // R15, R15D, R15W, R15B
};

const uint8_t TER_X64_REGISTER_SIZE_TABLE[TER_x64_REGISTER_COUNT] = {
	0x08, 0x04, 0x02, 0x01, 0x01, // RAX, EAX, AX, AH, AL
	0x08, 0x04, 0x02, 0x01, 0x01, // RBX, EBX, BX, BH, BL
	0x08, 0x04, 0x02, 0x01, 0x01, // RCX, ECX, CX, CH, CL
	0x08, 0x04, 0x02, 0x01, 0x01, // RDX, EDX, DX, DH, DL
	0x08, 0x04, 0x02, 0x01,       // RSI, ESI, SI, SIL
	0x08, 0x04, 0x02, 0x01,       // RDI, EDI, DI, DIL
	0x08, 0x04, 0x02, 0x01,       // RBP, EBP, BP, BPL
	0x08, 0x04, 0x02, 0x01,       // RSP, ESP, SP, SPL
	0x08, 0x04, 0x02,             // RIP, EIP, IP
	0x08, 0x04, 0x02, 0x01,       // R8,  R8D, R8W, R8B
	0x08, 0x04, 0x02, 0x01,       // R9,  R9D, R9W, R9B
	0x08, 0x04, 0x02, 0x01,       // R10, R10D, R10W, R10B
	0x08, 0x04, 0x02, 0x01,       // R11, R11D, R11W, R11B
	0x08, 0x04, 0x02, 0x01,       // R12, R12D, R12W, R12B
	0x08, 0x04, 0x02, 0x01,       // R13, R13D, R13W, R13B
	0x08, 0x04, 0x02, 0x01,       // R14, R14D, R14W, R14B
	0x08, 0x04, 0x02, 0x01,       // R15, R15D, R15W, R15B
};

const char* const TER_X64_REGISTER_MNEMONICS[TER_x64_REGISTER_COUNT] = {
	"rax", "eax", "ax", "ah", "al",
	"rbx", "ebx", "bx", "bh", "bl",
	"rcx", "ecx", "cx", "ch", "cl",
	"rdx", "edx", "dx", "dh", "dl",
	"rsi", "esi", "si", "sil",
	"rdi", "edi", "di", "dil",
	"rbp", "ebp", "bp", "bpl",
	"rsp", "esp", "sp", "spl",
	"rip", "eip", "ip",
	"r8", "r8d", "r8w", "r8b",
	"r9", "r9d", "r9w", "r9b",
	"r10", "r10d", "r10w", "r10b",
	"r11", "r11d", "r11w", "r11b",
	"r12", "r12d", "r12w", "r12b",
	"r13", "r13d", "r13w", "r13b",
	"r14", "r14d", "r14w", "r14b",
	"r15", "r15d", "r15w", "r15b",
};
