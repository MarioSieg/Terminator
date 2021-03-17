#ifndef TER_IMM_H
#define TER_IMM_H

#ifdef __cplusplus
extern "C" {
#endif

union ter_imm_t {
	unsigned char bytes[sizeof(unsigned long long int)];
	unsigned char u8;
	signed char i8;
	unsigned short int u16;
	signed short int i16;
	unsigned int u32;
	signed int i32;
	unsigned long long int u64;
	signed long long int i64;
	float f32;
	double f64;
};

extern unsigned char ter_imm_compute_size(union ter_imm_t imm);
extern void ter_imm_truncate(union ter_imm_t* imm, unsigned char max_bytes);

#ifdef __cplusplus
}
#endif

#endif
