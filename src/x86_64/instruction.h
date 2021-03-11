#ifndef TER_X64_INSTRUCTION_H
#define TER_X64_INSTRUCTION_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TER_X64_MAX_INSTRUCTION_BYTES 16

enum ter_x64_operand_flags_t {
	TER_X64_OPERAND_FLAGS_NONE = 0,

	TER_X64_OPERAND_FLAGS_REG8 = 1 << 1,
	TER_X64_OPERAND_FLAGS_REG16 = 1 << 2,
	TER_X64_OPERAND_FLAGS_REG32 = 1 << 3,
	TER_X64_OPERAND_FLAGS_REG64 = 1 << 4,

	TER_X64_OPERAND_FLAGS_REG8_AL = 1 << 5,
	TER_X64_OPERAND_FLAGS_REG16_AX = 1 << 6,
	TER_X64_OPERAND_FLAGS_REG32_EAX = 1 << 7,
	TER_X64_OPERAND_FLAGS_REG64_RAX = 1 << 8,

	TER_X64_OPERAND_FLAGS_MEM8 = 1 << 9,
	TER_X64_OPERAND_FLAGS_MEM16 = 1 << 10,
	TER_X64_OPERAND_FLAGS_MEM32 = 1 << 11,
	TER_X64_OPERAND_FLAGS_MEM64 = 1 << 12,

	TER_X64_OPERAND_FLAGS_IMM8 = 1 << 13,
	TER_X64_OPERAND_FLAGS_IMM16 = 1 << 14,
	TER_X64_OPERAND_FLAGS_IMM32 = 1 << 15,
	TER_X64_OPERAND_FLAGS_IMM64 = 1 << 16,
};

extern bool ter_x64_operand_flags_is_explicit(enum ter_x64_operand_flags_t flags);
extern bool ter_x64_operand_flags_is_accumulator(enum ter_x64_operand_flags_t flags);
extern bool ter_x64_operand_flags_is_immediate(enum ter_x64_operand_flags_t flags);
extern bool ter_x64_operand_flags_is_memory(enum ter_x64_operand_flags_t flags);
extern uint8_t ter_x64_operand_flags_compute_operand_size(enum ter_x64_operand_flags_t flags);

enum ter_x64_instruction_t {
	TER_X64_INSTRUCTION_ADC,

	TER_X64_INSTRUCTION_COUNT
};

#ifdef __cplusplus
}
#endif

#endif
