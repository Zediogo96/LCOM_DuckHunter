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

// Graphics modes
#define MODE_1024x768_INDEX 0x105
#define MODE_640x480_DIRECT 0x110
#define MODE_800x600_DIRECT 0x115
#define MODE_1280x1024_DIRECT 0x11A
#define MODE_1152x864_DIRECT 0x14C
#define MODE_CGA 0x03

// BUFFER MODEL

#define LINEAR_BUFFER BIT(14);

#endif // __VBE_H__
