#include "stream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stream_t {
	uint8_t* mem;
	size_t size;
	size_t cap;
};

bool stream_create(struct stream_t** const out) {
	return stream_with_capacity(out, 16);
}

bool stream_with_capacity(struct stream_t** const out, const size_t cap) {
	if (!out) {
		return false;
	}
	*out = malloc(sizeof(struct stream_t));
	if (!*out) {
		return false;
	}
	(*out)->cap = 16;
	(*out)->mem = malloc(sizeof(uint8_t) * (*out)->cap);
	(*out)->size = 0;
	return *out != NULL;
}

void stream_release(struct stream_t** const in) {
	if (!in) {
		return;
	}
	free((*in)->mem);
	free(*in);
	*in = NULL;
}

bool stream_push(struct stream_t* const self, const uint8_t value) {
	if (self->size + 1 >= self->cap) {
		self->cap <<= 1;
		uint8_t* const mem = realloc(self->mem, self->cap);
		if (!mem) {
			return false;
		}
		self->mem = mem;
	}
	self->mem[self->size++] = value;
	return true;
}

void stream_reset(struct stream_t* const self) {
	free(self->mem);
	self->mem = NULL;
	self->size = 0;
	self->cap = 0;
}

bool stream_encode_byte8(struct stream_t* const self, const uint8_t value) {
	return stream_push(self, value);
}

bool stream_encode_word16(struct stream_t* const self, const uint16_t value) {
	return stream_push(self, value & UINT16_C(0xFF)) && stream_push(self, value >> UINT16_C(8) & UINT16_C(0xFF));
}

bool stream_encode_dword32(struct stream_t* const self, const uint32_t value) {
	uint8_t written = 0;
	written += stream_push(self, value & UINT32_C(0xFF));
	written += stream_push(self, value >> UINT32_C(8) & UINT32_C(0xFF));
	written += stream_push(self, value >> UINT32_C(16) & UINT32_C(0xFF));
	written += stream_push(self, value >> UINT32_C(24) & UINT32_C(0xFF));
	return written == sizeof value;
}

bool stream_encode_qword64(struct stream_t* const self, const uint64_t value) {
	uint8_t written = 0;
	written += stream_push(self, value & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(8) & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(16) & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(24) & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(32) & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(40) & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(48) & UINT64_C(0xFF));
	written += stream_push(self, value >> UINT64_C(56) & UINT64_C(0xFF));
	return written == sizeof value;
}

bool stream_encode_single32(struct stream_t* const self, const float value) {
	const union {
		const uint32_t u;
		const float f;
	} castor = {.f = value};
	uint8_t written = 0;
	written += stream_push(self, castor.u & UINT32_C(0xFF));
	written += stream_push(self, castor.u >> UINT32_C(8) & UINT32_C(0xFF));
	written += stream_push(self, castor.u >> UINT32_C(16) & UINT32_C(0xFF));
	written += stream_push(self, castor.u >> UINT32_C(24) & UINT32_C(0xFF));
	return written == sizeof value;
}

bool stream_encode_double64(struct stream_t* const self, const double value) {
	const union {
		const uint64_t u;
		const double f;
	} castor = {.f = value};
	uint8_t written = 0;
	written += stream_push(self, castor.u & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(8) & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(16) & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(24) & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(32) & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(40) & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(48) & UINT64_C(0xFF));
	written += stream_push(self, castor.u >> UINT64_C(56) & UINT64_C(0xFF));
	return written == sizeof value;
}

void stream_dump(const struct stream_t* const self) {
	register const uint8_t* iter = self->mem;
	register const uint8_t* const end = self->mem + self->size - 1;
	while (iter != end) {
		printf("%02X ", *iter++);
	}
}
