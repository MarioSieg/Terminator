#include "machine.h"

uint8_t ter_pack_rex(const bool w, const bool r, const bool x, const bool b) {
	uint8_t rex = 0x40;
	rex ^= (-(uint8_t)b ^ rex) & 1 << 0;
	rex ^= (-(uint8_t)x ^ rex) & 1 << 1;
	rex ^= (-(uint8_t)r ^ rex) & 1 << 2;
	rex ^= (-(uint8_t)w ^ rex) & 1 << 3;
	return rex;
}

uint8_t ter_pack_trio(uint8_t bi01, uint8_t b234, uint8_t b567) {
	b567 &= ~0xF8;
	b234 &= ~0xF8;
	bi01 &= ~0xFC;
	b234 <<= 3;
	bi01 <<= 6;
	b567 |= b234 | bi01;
	return b567;
}
