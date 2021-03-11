#ifndef TER_IMM_H
#define TER_IMM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

union ter_imm_t {
	uint8_t bytes[sizeof(uint64_t)];
	uint8_t u8;
	int8_t i8;
	uint16_t u16;
	int16_t i16;
	uint32_t u32;
	int32_t i32;
	uint64_t u64;
	int64_t i64;
	float f32;
	double f64;
};

extern uint8_t ter_imm_compute_size(union ter_imm_t imm);
extern void ter_imm_truncate(union ter_imm_t* imm, uint8_t max_bytes);

#ifdef __cplusplus
}
#endif

#endif
