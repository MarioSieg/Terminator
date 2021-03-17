#include "machine.h"

unsigned char ter_pack_rex(const bool w, const bool r, const bool x, const bool b) {
	return (unsigned char)(0x40 | b | (unsigned char)x << 1 | (unsigned char)r << 2 | (unsigned char)w << 3);
}

unsigned char ter_pack_trio(const unsigned char bi01, const unsigned char b234, const unsigned char b567) {
	return (unsigned char)((b567 & ~0xF8) | (b234 & ~0xF8) << 3 | (bi01 & ~0xFC) << 6);
}
