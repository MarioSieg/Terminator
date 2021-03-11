#include "stream.h"
#include "branch_hints.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ter_stream_t {
	uint8_t* mem;
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
	(*out)->mem = malloc(sizeof(uint8_t) * (*out)->cap);
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

	uint8_t* const mem = realloc(self->mem, cap);
	if (unlikely(!mem)) {
		return false;
	}

	self->cap = cap;
	self->mem = mem;

	return true;
}

void ter_stream_reverse(struct ter_stream_t* const self) {
	register uint8_t* lo = self->mem;
	register uint8_t* hi = self->mem + self->size - 1;

	while (lo < hi) {
		const uint8_t tmp = *lo;
		*lo++ = *hi;
		*hi-- = tmp;
	}
}

void ter_stream_dyn_iter(struct ter_stream_t* const self, void (*const callback)(uint8_t*)) {
	register uint8_t* lo = self->mem;
	register uint8_t* const hi = self->mem + self->size;

	while (lo < hi) {
		callback(lo++);
	}
}

bool ter_stream_push(struct ter_stream_t* const self, const uint8_t value) {
	if (unlikely(self->size >= self->cap)) {
		self->cap <<= 1;
		uint8_t* const mem = realloc(self->mem, self->cap);
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

bool ter_stream_encode_byte8(struct ter_stream_t* const self, const uint8_t value) {
	return ter_stream_push(self, value);
}

bool ter_stream_encode_word16(struct ter_stream_t* const self, const uint16_t value) {
	return ter_stream_push(self, value & UINT16_C(0xFF)) && ter_stream_push(self, value >> UINT16_C(8) & UINT16_C(0xFF));
}

bool ter_stream_encode_dword32(struct ter_stream_t* const self, const uint32_t value) {
	if (unlikely(!ter_stream_reserve(self, self->size + sizeof value))) {
		return false;
	}
	memcpy(self->mem + self->size, &value, sizeof value);
	self->size += sizeof value;
	return true;
}

bool ter_stream_encode_qword64(struct ter_stream_t* const self, const uint64_t value) {
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

bool ter_stream_encode_db(struct ter_stream_t* self, const signed argc, ...) {
	va_list ptr;
	va_start(ptr, argc);
	signed num = 0;
	for (register signed i = 0; i < argc; ++i) {
		num += ter_stream_encode_byte8(self, va_arg(ptr, signed));
	}
	return num == argc;
}

bool ter_stream_encode_imm(struct ter_stream_t* const self, const union ter_imm_t imm) {
	const uint8_t size = ter_imm_compute_size(imm);
	return ter_stream_encode_memblock(self, &imm, size);
}

void ter_stream_dump(const struct ter_stream_t* const self) {
	register const uint8_t* iter = self->mem;
	register const uint8_t* const end = self->mem + self->size;
	while (iter < end) {
		printf("%02X ", *iter++);
	}
}

size_t ter_stream_write(const struct ter_stream_t* const self, FILE* const out) {
	return fwrite(self->mem, sizeof(uint8_t), self->size, out);
}

bool ter_stream_serialize(const struct ter_stream_t* const self, const char* const path) {
	FILE* f;
	#ifdef _MSC_VER
	const errno_t err = fopen_s(&f, path, "wb");
	if (unlikely(err)) {
		return false;
	}
	#else
	f = fopen(path, "wb");
	#endif
	if (unlikely(!f)) {
		return false;
	}
	const uint64_t size = (uint64_t)self->size;
	fwrite(&size, sizeof size, 1, f);
	ter_stream_write(self, f);
	fclose(f);
	return true;
}

bool ter_stream_deserialize(struct ter_stream_t** const out, const char* const path) {
	FILE* f;
	#ifdef _MSC_VER
	const errno_t err = fopen_s(&f, path, "rb");
	if (unlikely(err)) {
		return false;
	}
	#else
	f = fopen(path, "wb");
	#endif
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
	fread((*out)->mem, sizeof(uint8_t), size, f);
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
