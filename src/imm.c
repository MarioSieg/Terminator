#include "imm.h"

uint8_t ter_imm_compute_size(const union ter_imm_t imm) {
	register uint64_t v = imm.u64;
	register uint8_t bytes = 0;
	do {
		v >>= 8;
		++bytes;
	}
	while (v);
	return bytes;
}

void ter_imm_truncate(union ter_imm_t* const imm, const uint8_t max_bytes) {
	for (uint8_t i = max_bytes; i < (uint8_t)sizeof *imm; ++i) {
		imm->bytes[i] = 0;
	}
}
