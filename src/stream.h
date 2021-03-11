#ifndef ter_stream_H
#define ter_stream_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ter_stream_t;

extern bool ter_stream_create(struct ter_stream_t** out);
extern bool ter_stream_with_capacity(struct ter_stream_t** out, size_t cap);
extern void ter_stream_release(struct ter_stream_t** self);
extern bool ter_stream_reserve(struct ter_stream_t* self, size_t cap);
extern void ter_stream_reverse(struct ter_stream_t* self);
extern void ter_stream_dyn_iter(struct ter_stream_t* self, register void (* callback)(uint8_t*));

extern bool ter_stream_push(struct ter_stream_t* self, uint8_t value);
extern bool ter_stream_encode_byte8(struct ter_stream_t* self, uint8_t value);
extern bool ter_stream_encode_word16(struct ter_stream_t* self, uint16_t value);
extern bool ter_stream_encode_dword32(struct ter_stream_t* self, uint32_t value);
extern bool ter_stream_encode_qword64(struct ter_stream_t* self, uint64_t value);
extern bool ter_stream_encode_single32(struct ter_stream_t* self, float value);
extern bool ter_stream_encode_double64(struct ter_stream_t* self, double value);
extern bool ter_stream_encode_ascii(struct ter_stream_t* self, const char* str, size_t len);
extern bool ter_stream_encode_asciz(struct ter_stream_t* self, const char* str);
extern bool ter_stream_encode_memblock(struct ter_stream_t* self, const void* mem, size_t len);
extern bool ter_stream_encode_db(struct ter_stream_t* self, signed argc, ...);

extern uint8_t* ter_stream_get_mem(struct ter_stream_t* self);
extern size_t ter_stream_get_size(const struct ter_stream_t* self);
extern size_t ter_stream_get_cap(const struct ter_stream_t* self);

extern void ter_stream_dump(const struct ter_stream_t* self);
extern size_t ter_stream_write(const struct ter_stream_t* self, FILE* out);
extern bool ter_stream_serialize(const struct ter_stream_t* self, const char* path);
extern bool ter_stream_deserialize(struct ter_stream_t** out, const char* path);

#ifdef __cplusplus
}
#endif

#endif
