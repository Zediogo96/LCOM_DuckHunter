#include "duck.h"
#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_Duck(Database *db) {
  db->sprites->duck = create_sprite(db->images.duck_Up, (rand() % ((get_h_res() - 150) - 100 + 1)) + 150, 600, 4, 3, Up, Alive);
}

void update_Duck(Sprite *sprite) {

  if (sprite->state == Alive) {
    switch (sprite->direction) {
      case Up:
        if (sprite->y > 550)
          sprite->y -= sprite->yspeed;
        else {
          if (sprite->x >= (get_h_res() / 2)) {
            change_Sprite_Img(sprite, getDB()->images.duck_Right);
            sprite->direction = Right;
          }
          else {
            change_Sprite_Img(sprite, getDB()->images.duck_Left);
            sprite->direction = Left;
          }
        }
        break;
      case Left:

        if (sprite->x > 1)
          sprite->x -= sprite->xspeed;
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Right);
          sprite->direction = Right;
        }
        break;
      case Right:

        if ((sprite->x + sprite->width) < get_h_res())
          sprite->x += sprite->xspeed;
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Left);
          sprite->direction = Left;
        }
        break;

      default:
        break;
    }
  }
  if (sprite->state == Shot) {
    change_Sprite_Img(sprite, getDB()->images.duck_Falling);
    sprite->state = Falling;
  }

  if (sprite->state == Falling) {
    if (sprite->y < 600) {
      sprite->y = sprite->y + 5;
    }
    else {
      sprite->state = Dead;
      destroy_sprite(sprite);
    }
  }
}
