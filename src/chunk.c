#include "chunk.h"

#include <stdlib.h>
#include <string.h>
#undef NDEBUG
#include <assert.h>
#define NDEBUG

void chunk_push(struct chunk_t* const self, const uint8_t value) {
    if(self->heap) {
        if(self->size + 1 >= self->cap) {
            self->cap <<= 1;
            uint8_t* const mem = realloc(self->heap, self->cap);
            assert(mem);
            self->heap = mem;
        }
        *(self->heap + self->size++) = value;
    } else {
        if(self->size + 1 >= sizeof(self->stack) / sizeof(*self->stack)) {
            self->cap = sizeof(uint8_t) * (sizeof(self->stack) / sizeof(*self->stack)) * 4;
            self->heap = malloc(self->cap);
            assert(self->heap);
            memcpy(self->heap, self->stack, sizeof(self->stack));
        } else {
            *(self->stack + self->size++) = value;
        }
    }
}

void chunk_reset(struct chunk_t* const self) {
    if(self->heap) {
        free(self->heap);
    }
    self->heap = NULL;
    self->size = 0;
    self->cap = 0;
    memset(self->stack, 0, sizeof(self->stack));
}

void* chunk_encode_mem(struct chunk_t* const self, const void* const block, const size_t size) {
    register uint8_t* dst = self->heap ? self->heap : self->stack;
    register uint8_t* src = (uint8_t*)block;
    return memcpy(dst, src, !self->heap && size >= sizeof(self->stack) / sizeof(*self->stack) ? sizeof(self->stack) / sizeof(*self->stack) : size);
}
