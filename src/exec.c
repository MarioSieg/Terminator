#include <stdio.h>

#include "arch_parse.h"
#include "stream.h"

int main(const int argc, const char* const* const argv) {
	(void)argc;
	(void)argv;

	printf("Terminator (C) Copyright Mario Sieg 2020!\n");

	struct ter_arch_parse_instruction_info_t variation;
	char mnemonic[TER_ARCH_PARSE_MAX_MNEMONIC];
	char line[128] = "x80 | x2 | REG8, MEM8 & IMM8";

	const enum ter_arch_parse_result_t result = ter_arch_parse(&line, &mnemonic, &variation);
	if (result == TER_ARCH_PARSE_RESULT_VARIATION) {
		printf("opcode: 0x%x\n", variation.primary_opcode);
		printf("opcode_ex: 0x%x\n", variation.opcode_extension);
	}
	else {
		printf("%d\n", result);
	}

	struct ter_stream_t* ter_stream;
	ter_stream_create(&ter_stream);

	ter_stream_encode_qword64(ter_stream, 0xAABBCCDDEEFF);
	ter_stream_encode_asciz(ter_stream, "HelloWorld!");

	ter_stream_dump(ter_stream);

	ter_stream_release(&ter_stream);

	return 0;
}
