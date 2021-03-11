#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "arch_parse.h"
#include "branch_hints.h"

void ter_rem_space(register char* line) {
	register const char* iter = line;
	do {
		while (*iter == ' ') {
			++iter;
		}
	}
	while ((*line++ = *iter++));
}

void ter_rem_tabs(char* line) {
	register const char* iter = line;
	do {
		while (*iter == '\t') {
			++iter;
		}
	}
	while ((*line++ = *iter++));
}

enum ter_arch_parse_result_t ter_arch_parse(
	char (*const line_buf)[TER_ARCH_PARSE_MAX_LINE],
	char (*const mnemonic)[TER_ARCH_PARSE_MAX_MNEMONIC],
	struct ter_arch_parse_instruction_info_t* variation
) {
	if (unlikely(!line_buf || !*line_buf || !mnemonic || !variation)) {
		return TER_ARCH_PARSE_RESULT_ERROR;
	}

	register char* line = *line_buf;

	// remove spaces and tabs:
	ter_rem_space(line);
	ter_rem_tabs(line);

	const size_t len = strlen(line);
	if (unlikely(!len)) {
		return TER_ARCH_PARSE_RESULT_COMMENT;
	}

	// check for comment:
	if (unlikely(*line == TER_ARCH_PARSE_COMMENT)) {
		return TER_ARCH_PARSE_RESULT_COMMENT;
	}

	// check if line end with ':'
	// and begins a new instruction:
	if (unlikely(line[len - 1] == TER_ARCH_PARSE_PIN)) {
		line[len - 1] = '\0';

		// if line is too large for the mnemonic buffer, return error:
		if (unlikely(len >= TER_ARCH_PARSE_MAX_MNEMONIC)) {
			return TER_ARCH_PARSE_RESULT_ERROR;
		}

		strncpy(*mnemonic, line, len - 1);
		return TER_ARCH_PARSE_RESULT_MNEMONIC;
	}

	// continue parsing variation:
	// first comes the opcode written in hex with a 0x prefix:
	const char* const prefix = TER_ARCH_HEX_PREFIX;

	// if line does not begin with 0x (opcode), error:
	if (unlikely(*line != *prefix || line[1] != prefix[1])) {
		return TER_ARCH_PARSE_RESULT_ERROR;
	}

	// skip 0x
	line += 2;

	// find next separator to copy length '|':
	char* sep = strchr(line, TER_ARCH_PARSE_SEPARATOR);
	if (unlikely(!sep)) {
		return TER_ARCH_PARSE_RESULT_ERROR;
	}

	// copy number literal to buffer
	const ptrdiff_t sep_dist = sep - line;
	char num_buf[16];
	strncpy(num_buf, line, sep_dist);
	num_buf[sep_dist] = '\0';

	// convert hex opcode to long
	// 16 = hex radix
	char* end;
	const long opcode = strtol(num_buf, &end, 16);
	if (unlikely(end == num_buf || *end != '\0' || errno == ERANGE)) {
		return TER_ARCH_PARSE_RESULT_ERROR;
	}

	// forward to separator and skip it too:
	line = sep;
	++line;

	// todo: parse flags

	variation->primary_opcode = opcode & 0xFF;

	return TER_ARCH_PARSE_RESULT_VARIATION;
}
