#include <stdio.h>
#include "stream.h"

signed main(const signed argc, const char* const* const argv) {
	printf("Terminator (C) Copyright Mario Sieg 2020!\n");

	struct stream_t* stream;
	stream_create(&stream);

	stream_encode_byte8(stream, 0xFF);
	stream_encode_byte8(stream, 0xAA);
	stream_encode_byte8(stream, 0xBB);
	stream_encode_db(stream, 5, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE);
	stream_encode_qword64(stream, 0xAABBCCDDEEFF);

	stream_dump(stream);

	stream_release(&stream);

	return 0;
}
