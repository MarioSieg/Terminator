#include "instruction.h"

bool ter_x64_operand_flags_is_explicit(const enum ter_x64_operand_flags flags) {
	return flags > 0 && flags <= TER_X64_OPERAND_FLAGS_REG64_RAX;
}

bool ter_x64_operand_flags_is_accumulator(const enum ter_x64_operand_flags flags) {
	return flags >= TER_X64_OPERAND_FLAGS_REG8_AL && flags <= TER_X64_OPERAND_FLAGS_REG64_RAX;
}

bool ter_x64_operand_flags_is_immediate(const enum ter_x64_operand_flags flags) {
	return flags >= TER_X64_OPERAND_FLAGS_IMM8 && flags <= TER_X64_OPERAND_FLAGS_IMM64;
}

bool ter_x64_operand_flags_is_memory(const enum ter_x64_operand_flags flags) {
	return flags >= TER_X64_OPERAND_FLAGS_MEM8 && flags <= TER_X64_OPERAND_FLAGS_MEM64;
}

uint8_t ter_x64_operand_flags_compute_operand_size(const enum ter_x64_operand_flags flags) {
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
