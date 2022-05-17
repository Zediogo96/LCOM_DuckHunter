#ifndef __VIDEO_GR_H__
#define __VIDEO_GR_H__

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include "vbe.h"

void *(vg_init) (uint16_t mode);

int (change_pixel_color)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif // __VIDEO_GR_H__
