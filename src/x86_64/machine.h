#ifndef TER_X64_MACHINE_H
#define TER_X64_MACHINE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TER_X64_OPERAND_SIZE_OVR			0x66
#define TER_X64_ADDRESS_SIZE_OVR			0x67
#define TER_X64_MOD_REGISTER_INDIRECT		0x00
#define TER_X64_MOD_BYTE_SIGNED_DISPLACE	0x01
#define TER_X64_MOD_DWORD_SIGNED_DISPLACE	0x02
#define TER_X64_MOD_REGISTER_ADDRESS		0x03

extern unsigned char ter_pack_rex(bool w, bool r, bool x, bool b);
extern unsigned char ter_pack_trio(unsigned char bi01, unsigned char b234, unsigned char b567);

#ifdef __cplusplus
}
#endif

#endif
