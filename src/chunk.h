#ifndef CHUNK_H
#define CHUNK_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define CHUNK_STACK_SIZE 16

struct chunk_t {
    uint8_t stack[CHUNK_STACK_SIZE];
    uint8_t* heap;
    size_t size;
    size_t cap;
};

static inline void chunk_init(struct chunk_t* const self) {
    self->heap = NULL;
    self->size = 0;
    self->cap = sizeof(self->stack) / sizeof(*self->stack);
}

extern void chunk_push(struct chunk_t* const self, const uint8_t value);

extern void chunk_reset(struct chunk_t* const self);

extern void* chunk_encode_mem(struct chunk_t* const self, const void* const block, const size_t size);

static inline void chunk_encode_byte8(struct chunk_t* const self, const uint8_t value) {
    chunk_push(self, value);
}

static inline void chunk_encode_word16(struct chunk_t* const self, const uint16_t value) {
    chunk_encode_mem(self, &value, sizeof(value));
}

static inline void chunk_encode_dword32(struct chunk_t* const self, const uint32_t value) {
    chunk_encode_mem(self, &value, sizeof(value));
}

static inline void chunk_encode_qword64(struct chunk_t* const self, const uint64_t value) {
    chunk_encode_mem(self, &value, sizeof(value));
}

static inline void chunk_encode_single32(struct chunk_t* const self, const float value) {
    chunk_encode_mem(self, &value, sizeof(value));
}

static inline void chunk_encode_double64(struct chunk_t* const self, const double value) {
    chunk_encode_mem(self, &value, sizeof(value));
}

static inline void chunk_encode_asciz(struct chunk_t* const self, const char* const str) {
    const size_t len = strlen(str);
    chunk_encode_mem(self, str, len);
}

#endif
