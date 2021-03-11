#include "instruction.h"

bool ter_x64_operand_flags_is_explicit(const enum ter_x64_operand_flags_t flags) {
	return flags > 0 && flags <= TER_X64_OPERAND_FLAGS_REG64_RAX;
}

bool ter_x64_operand_flags_is_accumulator(const enum ter_x64_operand_flags_t flags) {
	return flags >= TER_X64_OPERAND_FLAGS_REG8_AL && flags <= TER_X64_OPERAND_FLAGS_REG64_RAX;
}

bool ter_x64_operand_flags_is_immediate(const enum ter_x64_operand_flags_t flags) {
	return flags >= TER_X64_OPERAND_FLAGS_IMM8 && flags <= TER_X64_OPERAND_FLAGS_IMM64;
}

bool ter_x64_operand_flags_is_memory(const enum ter_x64_operand_flags_t flags) {
	return flags >= TER_X64_OPERAND_FLAGS_MEM8 && flags <= TER_X64_OPERAND_FLAGS_MEM64;
}

uint8_t ter_x64_operand_flags_compute_operand_size(const enum ter_x64_operand_flags_t flags) {
	if (flags == TER_X64_OPERAND_FLAGS_REG64_RAX || flags & TER_X64_OPERAND_FLAGS_REG64 || flags & TER_X64_OPERAND_FLAGS_MEM64 || flags & TER_X64_OPERAND_FLAGS_IMM64) {
		return 8;
	}
	if (flags == TER_X64_OPERAND_FLAGS_REG32_EAX || flags & TER_X64_OPERAND_FLAGS_REG32 || flags & TER_X64_OPERAND_FLAGS_MEM32 || flags & TER_X64_OPERAND_FLAGS_IMM32) {
		return 4;
	}
	if (flags == TER_X64_OPERAND_FLAGS_REG16_AX || flags & TER_X64_OPERAND_FLAGS_REG16 || flags & TER_X64_OPERAND_FLAGS_MEM16 || flags & TER_X64_OPERAND_FLAGS_IMM16) {
		return 2;
	}
	return 1;
}

#define NONE TER_X64_OPERAND_FLAGS_NONE
#define REG8 TER_X64_OPERAND_FLAGS_REG8
#define REG16 TER_X64_OPERAND_FLAGS_REG16
#define REG32 TER_X64_OPERAND_FLAGS_REG32
#define REG64 TER_X64_OPERAND_FLAGS_REG64
#define REG8_AL TER_X64_OPERAND_FLAGS_REG8_AL
#define REG16_AX TER_X64_OPERAND_FLAGS_REG16_AX
#define REG32_EAX TER_X64_OPERAND_FLAGS_REG32_EAX
#define REG64_RAX TER_X64_OPERAND_FLAGS_REG64_RAX
#define MEM8 TER_X64_OPERAND_FLAGS_MEM8
#define MEM16 TER_X64_OPERAND_FLAGS_MEM16
#define MEM32 TER_X64_OPERAND_FLAGS_MEM32
#define MEM64 TER_X64_OPERAND_FLAGS_MEM64
#define IMM8 TER_X64_OPERAND_FLAGS_IMM8
#define IMM16 TER_X64_OPERAND_FLAGS_IMM16
#define IMM32 TER_X64_OPERAND_FLAGS_IMM32
#define IMM64 TER_X64_OPERAND_FLAGS_IMM64
#define GPR (REG8 | REG8_AL | REG16 | REG16_AX | REG32 | REG32_EAX | REG64 | REG64_RAX)
#define MEM (MEM8 | MEM16 | MEM32 | MEM64)
#define IMM (IMM8 | IMM16 | IMM32 | IMM64)
#define ACC (REG8_AL | REG16_AX | REG32_EAX | REG64_RAX)
#define ACC_16_32_64 (REG16_AX | REG32_EAX | REG64_RAX)
#define GPR_16_32_64 (REG16 | REG16_AX | REG32 | REG32_EAX | REG64 | REG64_RAX)
#define MEM_16_32_64 (MEM16 | MEM32 | MEM64)
#define GPR_MEM_16_32_64 (GPR_16_32_64 | MEM_16_32_64)
#define REG_MEM_8 (REG8 | MEM8)
#define IMM_16_32 (IMM16 | IMM32)
