#include "machine.h"

unsigned char ter_pack_rex(const bool w, const bool r, const bool x, const bool b) {
	register unsigned char rex = 0x40;
	rex ^= (-(unsigned char)b ^ rex) & 1 << 0;
	rex ^= (-(unsigned char)x ^ rex) & 1 << 1;
	rex ^= (-(unsigned char)r ^ rex) & 1 << 2;
	rex ^= (-(unsigned char)w ^ rex) & 1 << 3;
	return rex;
}

unsigned char ter_pack_trio(const unsigned char bi01, const unsigned char b234, const unsigned char b567) {
	return (unsigned char)(b567 & ~0xF8 | (b234 & ~0xF8) << 3 | (bi01 & ~0xFC) << 6);
}
