#include <stdio.h>
#include "stream.h"

signed main(const signed argc, const char* const* const argv) {
	(void)argc;
	(void)argv;

	printf("Terminator (C) Copyright Mario Sieg 2020!\n");

	struct stream_t* stream;
	stream_create(&stream);

	stream_encode_qword64(stream, 0xAABBCCDDEEFF);
	stream_encode_asciz(stream, "HelloWorld!");

	stream_dump(stream);

	stream_release(&stream);

	return 0;
}
