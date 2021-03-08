#ifndef stream_H
#define stream_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct stream_t;

extern bool stream_create(struct stream_t** const out);
extern bool stream_with_capacity(struct stream_t** const out, const size_t cap);
extern void stream_release(struct stream_t** const self);
extern bool stream_reserve(struct stream_t* const self, const size_t cap);

extern bool stream_push(struct stream_t* const self, const uint8_t value);
extern bool stream_encode_byte8(struct stream_t* const self, const uint8_t value);
extern bool stream_encode_word16(struct stream_t* const self, const uint16_t value);
extern bool stream_encode_dword32(struct stream_t* const self, const uint32_t value);
extern bool stream_encode_qword64(struct stream_t* const self, const uint64_t value);
extern bool stream_encode_single32(struct stream_t* const self, const float value);
extern bool stream_encode_double64(struct stream_t* const self, const double value);
extern bool stream_encode_ascii(struct stream_t* const self, const char* const str, const size_t len);
extern bool stream_encode_asciz(struct stream_t* const self, const char* const str);
extern bool stream_encode_memblock(struct stream_t* const self, const void* const mem, const size_t len);

extern uint8_t* stream_get_mem(struct stream_t* const self);
extern size_t stream_get_size(struct stream_t* const self);
extern size_t stream_get_cap(struct stream_t* const self);

extern void stream_dump(const struct stream_t* const self);
extern size_t stream_write(const struct stream_t* const self, FILE* const out);


#endif
