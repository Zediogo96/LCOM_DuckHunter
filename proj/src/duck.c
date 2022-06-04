#include "duck.h"
#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createDucksArray() {
  getDB()->sprites->ducks = (Sprite **) malloc(TOTAL_NR_OF_DUCKS * sizeof(Sprite *));

  for (int i = 0; i < TOTAL_NR_OF_DUCKS; ++i) getDB()->sprites->ducks[i] = NULL;
}

void create_Duck() {

  int i = 0;
  while (getDB()->sprites->ducks[i] != NULL) ++i;

  if (i < TOTAL_NR_OF_DUCKS)
    getDB()->sprites->ducks[i] = create_sprite(getDB()->images.duck_Up, (rand() % ((get_h_res() - 150) - 100 + 1)) + 150, 600, 10, 10, Up, Alive);
}

void update_ducks() {
  for (int i = 0; i < TOTAL_NR_OF_DUCKS; ++i) {
    if (getDB()->sprites->ducks[i] != NULL) {
      update_Duck(getDB()->sprites->ducks[i], i);
    }
  }
}

void update_Duck(Sprite *sprite, uint8_t idx) {

  if (sprite->y == 0) {
    getDB()->sprites->ducks[idx] = NULL; 
    destroy_sprite(sprite);
    getDB()->lives--;
  }

  if (sprite->state == Dead) {
    getDB()->sprites->ducks[idx] = NULL; // To de-allocate memory within the duck array 
    destroy_sprite(sprite);
  }

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
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Right);
          sprite->direction = Up_Right;
        }
        break;
      case Right:

        if ((sprite->x + sprite->width) < get_h_res())
          sprite->x += sprite->xspeed;
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Left);
          sprite->direction = Up_Left;
        }
        break;

      case Up_Left:
        if ((sprite->x > 0) && (sprite->y > 0)) {
          sprite->x -= sprite->xspeed;
          sprite->y -= sprite->yspeed;
        }
        break;

      case Up_Right:
        if ((sprite->x + sprite->width) < get_h_res() && (sprite->y > 0)) {
          sprite->x += sprite->xspeed;
          sprite->y -= sprite->yspeed;
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
    else       sprite->state = Dead;
    }  
}
