#include "stream.h"

#include <stdarg.h>
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

void stream_release(struct stream_t** const self) {
	if (!self) {
		return;
	}
	free((*self)->mem);
	free(*self);
	*self = NULL;
}

bool stream_reserve(struct stream_t* const self, const size_t cap) {
	if (cap < self->cap) {
		return true;
	}

	uint8_t* mem = realloc(self->mem, cap);
	if (!mem) {
		return false;
	}

	self->cap = cap;
	self->mem = mem;

	return true;
}

void stream_reverse(struct stream_t* const self) {
	register uint8_t* lo = self->mem;
	register uint8_t* hi = self->mem + self->size - 1;

	while (lo < hi) {
		const uint8_t tmp = *lo;
		*lo++ = *hi;
		*hi-- = tmp;
	}
}

void stream_dyn_iter(struct stream_t* const self, void (*const callback)(uint8_t*)) {
	register uint8_t* lo = self->mem;
	register uint8_t* hi = self->mem + self->size;

	while (lo < hi) {
		callback(lo++);
	}
}

bool stream_push(struct stream_t* const self, const uint8_t value) {
	if (self->size >= self->cap) {
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

bool stream_encode_ascii(struct stream_t* const self, const char* const str, const size_t len) {
	if (!stream_reserve(self, self->size + len)) {
		return false;
	}
	register const char* iter = str;
	register const char* end = str + len;
	register size_t written = 0;
	while (iter < end) {
		written += stream_encode_byte8(self, *iter++);
	}
	return written == len;
}

bool stream_encode_asciz(struct stream_t* const self, const char* const str) {
	const size_t len = strlen(str);
	return stream_encode_ascii(self, str, len) && stream_encode_byte8(self, '\0');
}

bool stream_encode_memblock(struct stream_t* const self, const void* const mem, const size_t len) {
	return stream_encode_ascii(self, (const char*)mem, len);
}

bool stream_encode_db(struct stream_t* self, const signed argc, ...) {
	va_list ptr;
	va_start(ptr, argc);
	int num = 0;
	for (register signed i = 0; i < argc; ++i) {
		num += stream_encode_byte8(self, va_arg(ptr, uint8_t));
	}
	return num == argc;
}

void stream_dump(const struct stream_t* const self) {
	register const uint8_t* iter = self->mem;
	register const uint8_t* const end = self->mem + self->size;
	while (iter < end) {
		printf("%02X ", *iter++);
	}
}

size_t stream_write(const struct stream_t* const self, FILE* const out) {
	return fwrite(self->mem, sizeof(uint8_t), self->size, out);
}

bool stream_serialize(const struct stream_t* const self, const char* const path) {
	FILE* const f = fopen(path, "wb");
	if (!f) {
		return false;
	}
	const uint64_t size = (uint64_t)self->size;
	fwrite(&size, sizeof size, 1, f);
	stream_write(self, f);
	fclose(f);
	return true;
}

bool stream_deserialize(struct stream_t** const out, const char* const path) {
	FILE* const f = fopen(path, "rb");
	if (!f) {
		return false;
	}
	uint64_t size = 0;
	fread(&size, sizeof size, 1, f);
	if (!size) {
		return false;
	}
	if (!stream_with_capacity(out, size)) {
		return false;
	}
	fread(&(*out)->mem, sizeof(uint8_t), size, f);
	(*out)->size = (*out)->cap = (size_t)size;
	return true;
}

uint8_t* stream_get_mem(struct stream_t* const self) {
	return self->mem;
}

size_t stream_get_size(const struct stream_t* const self) {
	return self->size;
}

size_t stream_get_cap(const struct stream_t* const self) {
	return self->cap;
}
