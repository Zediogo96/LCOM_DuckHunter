#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "video_gr.h"

/**
 * @brief Struct to keep sprite info
 */
typedef struct {
int x, y; // current position
int width, height; // dimensions
int xspeed, yspeed; // current speed
uint8_t *map; // the pixmap
} Sprite;

Sprite *create_sprite(xpm_image_t img, int x, int y, int xspeed, int yspeed);

void destroy_sprite(Sprite *sp);

int draw_sprite(Sprite *sp, char *base);


#endif // _SPRITE_H
