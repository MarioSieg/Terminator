#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stream.h"
#include "branch_hints.h"

struct ter_stream_t {
	unsigned char* mem;
	size_t size;
	size_t cap;
};

bool ter_stream_create(struct ter_stream_t** const out) {
	return ter_stream_with_capacity(out, 16);
}

bool ter_stream_with_capacity(struct ter_stream_t** const out, const size_t cap) {
	if (unlikely(!out)) {
		return false;
	}
	*out = malloc(sizeof(struct ter_stream_t));
	if (unlikely(!*out)) {
		return false;
	}
	(*out)->cap = cap;
	(*out)->mem = malloc(sizeof(unsigned char) * (*out)->cap);
	(*out)->size = 0;
	return *out != NULL;
}

void ter_stream_release(struct ter_stream_t** const self) {
	if (unlikely(!self)) {
		return;
	}
	free((*self)->mem);
	free(*self);
	*self = NULL;
}

bool ter_stream_reserve(struct ter_stream_t* const self, const size_t cap) {
	if (likely(cap < self->cap)) {
		return true;
	}

	unsigned char* const mem = realloc(self->mem, cap);
	if (unlikely(!mem)) {
		return false;
	}

	self->cap = cap;
	self->mem = mem;

	return true;
}

void ter_stream_reverse(struct ter_stream_t* const self) {
	register unsigned char* lo = self->mem;
	register unsigned char* hi = self->mem + self->size - 1;

	while (lo < hi) {
		const unsigned char tmp = *lo;
		*lo++ = *hi;
		*hi-- = tmp;
	}
}

void ter_stream_dyn_iter(struct ter_stream_t* const self, void (*const callback)(unsigned char*)) {
	register unsigned char* lo = self->mem;
	register unsigned char* const hi = self->mem + self->size;

	while (lo < hi) {
		callback(lo++);
	}
}

bool ter_stream_push(struct ter_stream_t* const self, const unsigned char value) {
	if (unlikely(self->size >= self->cap)) {
		self->cap <<= 1;
		unsigned char* const mem = realloc(self->mem, self->cap);
		if (unlikely(!mem)) {
			return false;
		}
		self->mem = mem;
	}
	self->mem[self->size++] = value;
	return true;
}

void ter_stream_reset(struct ter_stream_t* const self) {
	free(self->mem);
	self->mem = NULL;
	self->size = 0;
	self->cap = 0;
}

bool ter_stream_encode_byte8(struct ter_stream_t* const self, const unsigned char value) {
	return ter_stream_push(self, value);
}

bool ter_stream_encode_word16(struct ter_stream_t* const self, const unsigned short int value) {
	return ter_stream_push(self, value & 0xFF) && ter_stream_push(self, value >> 8 & 0xFF);
}

bool ter_stream_encode_dword32(struct ter_stream_t* const self, const unsigned int value) {
	if (unlikely(!ter_stream_reserve(self, self->size + sizeof value))) {
		return false;
	}
	memcpy(self->mem + self->size, &value, sizeof value);
	self->size += sizeof value;
	return true;
}

bool ter_stream_encode_qword64(struct ter_stream_t* const self, const unsigned long long int value) {
	if (unlikely(!ter_stream_reserve(self, self->size + sizeof value))) {
		return false;
	}
	memcpy(self->mem + self->size, &value, sizeof value);
	self->size += sizeof value;
	return true;
}

bool ter_stream_encode_single32(struct ter_stream_t* const self, const float value) {
	if (unlikely(!ter_stream_reserve(self, self->size + sizeof value))) {
		return false;
	}
	memcpy(self->mem + self->size, &value, sizeof value);
	self->size += sizeof value;
	return true;
}

bool ter_stream_encode_double64(struct ter_stream_t* const self, const double value) {
	if (unlikely(!ter_stream_reserve(self, self->size + sizeof value))) {
		return false;
	}
	memcpy(self->mem + self->size, &value, sizeof value);
	self->size += sizeof value;
	return true;
}

bool ter_stream_encode_ascii(struct ter_stream_t* const self, const char* const str, const size_t len) {
	if (unlikely(!ter_stream_reserve(self, self->size + len))) {
		return false;
	}
	memcpy(self->mem + self->size, str, sizeof(char) * len);
	self->size += len;
	return true;
}

bool ter_stream_encode_asciz(struct ter_stream_t* const self, const char* const str) {
	const size_t len = strlen(str);
	return ter_stream_encode_ascii(self, str, len) && ter_stream_encode_byte8(self, '\0');
}

bool ter_stream_encode_memblock(struct ter_stream_t* const self, const void* const mem, const size_t len) {
	return ter_stream_encode_ascii(self, (const char* const)mem, len);
}

bool ter_stream_encode_db(struct ter_stream_t* self, const int argc, ...) {
	va_list ptr;
	va_start(ptr, argc);
	signed num = 0;
	for (register int i = 0; i < argc; ++i) {
		num += ter_stream_encode_byte8(self, va_arg(ptr, int));
	}
	return num == argc;
}

bool ter_stream_encode_imm(struct ter_stream_t* const self, const union ter_imm_t imm) {
	const unsigned char size = ter_imm_compute_size(imm);
	return ter_stream_encode_memblock(self, &imm, size);
}

void ter_stream_dump(const struct ter_stream_t* const self) {
	register const unsigned char* iter = self->mem;
	register const unsigned char* const end = self->mem + self->size;
	while (iter < end) {
		printf("%02X ", *iter++);
	}
}

size_t ter_stream_write(const struct ter_stream_t* const self, FILE* const out) {
	return fwrite(self->mem, sizeof(unsigned char), self->size, out);
}

bool ter_stream_serialize(const struct ter_stream_t* const self, const char* const path) {
	FILE* f = fopen(path, "wb");
	if (unlikely(!f)) {
		return false;
	}
	const uint64_t size = self->size;
	fwrite(&size, sizeof size, 1, f);
	ter_stream_write(self, f);
	fclose(f);
	return true;
}

bool ter_stream_deserialize(struct ter_stream_t** const out, const char* const path) {
	FILE* f = fopen(path, "wb");
	if (unlikely(!f)) {
		return false;
	}
	uint64_t size = 0;
	fread(&size, sizeof size, 1, f);
	if (unlikely(!size)) {
		return false;
	}
	if (unlikely(!ter_stream_with_capacity(out, size))) {
		return false;
	}
	fread((*out)->mem, sizeof(unsigned char), size, f);
	(*out)->size = (*out)->cap = (size_t)size;
	return true;
}

uint8_t* ter_stream_get_mem(struct ter_stream_t* const self) {
	return self->mem;
}

size_t ter_stream_get_size(const struct ter_stream_t* const self) {
	return self->size;
}

size_t ter_stream_get_cap(const struct ter_stream_t* const self) {
	return self->cap;
}
