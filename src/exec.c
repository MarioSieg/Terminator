#include <stdio.h>
#include "stream.h"

int main(const int argc, const char* const* const argv) {
	printf("Terminator (C) Copyright Mario Sieg 2020!\n");

	struct stream_t* stream;
	stream_create(&stream);

	stream_encode_byte8(stream, 0xFF);
	stream_encode_byte8(stream, 0xAA);
	stream_encode_byte8(stream, 0xBB);
	stream_reverse(stream);

	stream_dump(stream);

	stream_release(&stream);

	return 0;
}
