#include <stdio.h>
#include <string.h>
#include "stream.h"

signed main(const signed argc, const char* const* const argv) {
	(void)argc;
	(void)argv;

	printf("Terminator (C) Copyright Mario Sieg 2020!\n");

	struct ter_stream_t* ter_stream;
	ter_stream_create(&ter_stream);

	ter_stream_encode_qword64(ter_stream, 0xAABBCCDDEEFF);
	ter_stream_encode_asciz(ter_stream, "HelloWorld!");

	ter_stream_dump(ter_stream);

	ter_stream_release(&ter_stream);

	return 0;
}
