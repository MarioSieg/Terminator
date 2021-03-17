#include "imm.h"

unsigned char ter_imm_compute_size(const union ter_imm_t imm) {
	register unsigned long long int v = imm.u64;
	register unsigned char bytes = 0;
	do {
		v >>= 8;
		++bytes;
	}
	while (v);
	return bytes;
}

void ter_imm_truncate(union ter_imm_t* const imm, const unsigned char max_bytes) {
	for (register unsigned char i = max_bytes; i < (unsigned char)sizeof *imm; ++i) {
		imm->bytes[i] = 0;
	}
}
