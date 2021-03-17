#ifndef TER_ARCH_PARSE_H
#define TER_ARCH_PARSE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TER_ARCH_PARSE_MAX_LINE 128
#define TER_ARCH_PARSE_MAX_MNEMONIC 16
#define TER_ARCH_PARSE_COMMENT '#'
#define TER_ARCH_PARSE_SEPARATOR '|'
#define TER_ARCH_PARSE_LIST ','
#define TER_ARCH_PARSE_PIN ':'
#define TER_ARCH_HEX_PREFIX 'x'
#define TER_ARCH_NONE "NA"

struct ter_arch_parse_instruction_info_t {
	uint8_t mnemonic_len;

	uint8_t primary_opcode;

	uint16_t operand_flags[4];
	uint8_t operand_flags_len;

	uint8_t opcode_extension;
};

extern void ter_rem_space(register char* line);
extern void ter_rem_tabs(register char* line);

enum ter_arch_parse_result_t {
	TER_ARCH_PARSE_RESULT_ERROR,
	TER_ARCH_PARSE_RESULT_COMMENT,
	TER_ARCH_PARSE_RESULT_MNEMONIC,
	TER_ARCH_PARSE_RESULT_VARIATION
};

extern enum ter_arch_parse_result_t ter_arch_parse(
	char (*line_buf)[TER_ARCH_PARSE_MAX_LINE],
	char (*mnemonic)[TER_ARCH_PARSE_MAX_MNEMONIC],
	struct ter_arch_parse_instruction_info_t* variation
);

#ifdef __cplusplus
}
#endif

#endif
