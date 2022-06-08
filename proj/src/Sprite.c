#include "Include/Sprite.h"

Sprite *create_sprite(xpm_image_t img, int x, int y, int xspeed_, int yspeed_, enum Direction direction_, enum State state_) {
  // allocate space for the "object"
  Sprite *sp = (Sprite *) malloc(sizeof(Sprite));
  // xpm_image_t img;
  if (sp == NULL)
    return NULL;
  // read the sprite pixmap
  sp->map = img.bytes;
  if (sp->map == NULL) {
    free(sp);
    return NULL;
  }
  sp->x = x;
  sp->y = y;
  sp->width = img.width;
  sp->height = img.height;
  sp->xspeed = xspeed_;
  sp->yspeed = yspeed_;
  sp->direction = direction_;
  sp->state = state_;

  return sp;
}

void destroy_sprite(Sprite *sp) {
  if (sp == NULL)
    return;

  free(sp->map);

  free(sp);
  sp = NULL;
}

int draw_sprite(Sprite *sp) {
  uint32_t transparent = xpm_transparency_color(XPM_8_8_8_8);
  uint32_t *color = (uint32_t *) sp->map;

  for (int i = 0; i < sp->height; ++i) {
    if ((sp->y + i) >= (int) get_v_res())
      continue;

    for (int j = 0; j < sp->width; ++j) {
      if ((sp->x + j) >= (int) get_h_res())
        continue;

      if (*color != transparent) {
        if (change_pixel_color(sp->x + j, sp->y + i, *color) != 0) {
          return 1;
        }
      }

      color++;
    }
  }

  return 0;
}

void change_Sprite_Img(Sprite *sprite, xpm_image_t img) {
  sprite->map = img.bytes;
  sprite->width = img.width;
  sprite->height = img.height;
}
