#ifndef __VIDEO_GR_H__
#define __VIDEO_GR_H__

#include "vbe.h"
#include <lcom/lcf.h>
#include <machine/int86.h>
#include <minix/sysutil.h>

void *(vg_init) (uint16_t mode);

#endif // __VIDEO_GR_H__
