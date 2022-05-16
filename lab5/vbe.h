#ifndef __VBE_H__
#define __VBE_H__

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <minix/sysutil.h>

// BIOS SERVICES
#define BIOS_VID_CARD 0x10

// AH consts
#define VBE_CALL 0x4F

#define AH_CALL_FAILED 0x01
#define AH_NOT_SUPPORTED_CONF 0x02
#define AH_NOT_SUPPORTED_MODE 0x03

// FUNCTIONS
#define SET_VBE_MODE 0x02
#define GET_VBE_MODE_INFO 0x01
#define GET_VBE_CONTROLLER_INFO 0x00

// BUFFER MODEL

#define LINEAR_BUFFER BIT(14);

void * vbe_map_vram(unsigned int phys_base_ptr, unsigned int vram_size);

int vbe_set_mode(uint16_t mode);

#endif // __VBE_H__
