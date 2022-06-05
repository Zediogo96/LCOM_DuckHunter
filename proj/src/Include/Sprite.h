#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "video_gr.h"

enum Direction { Right,
                 Left,
                 Up_Right,
                 Up_Left,
                 Up,
                 Down,
                 default_Dir };
enum State { Dead,
             Alive,
             Shot,
             Falling,
             default_State };
/**
 * @brief Struct to keep sprite info
 */
typedef struct {
  int x, y;           // current position
  int width, height;  // dimensions
  int xspeed, yspeed; // current speed
  uint8_t *map;       // the pixmap
  enum Direction direction;
  enum State state;
} Sprite;

Sprite *create_sprite(xpm_image_t img, int x, int y, int xspeed, int yspeed, enum Direction direction, enum State state);

void destroy_sprite(Sprite *sp);

int draw_sprite(Sprite *sp);

void change_Sprite_Img(Sprite *sprite, xpm_image_t img);

#endif // _SPRITE_H
