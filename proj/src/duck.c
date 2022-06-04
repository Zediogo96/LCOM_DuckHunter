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
  srand(time(NULL));
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
enum Direction generaterandomdir(enum Direction direction){
  srand(time(NULL));
  int index = rand() % 8;
  enum Direction Up[] = {Right,Left,Up_Right,Up_Left,Up};
  enum Direction Right[] = {Right,Up_Right};
  enum Direction Left[] = {Left,Up_Left};
  enum Direction upright[] = {Up_Right,Right,Up};
  enum Direction upleft[] = {Left,Up_Left,Up};

  switch (direction)
  {
  case Up:
    index = rand() % 5;
    return Up[index];
    break;
  case Right:
    index = rand() % 2;
    return Right[index];
    break;
  case Left:
    index = rand() % 2;
    return Left[index];
    break;
  case Up_Right:
    index = rand() % 3;
    return upright[index];
    break;
  case Up_Left:
    index = rand() % 3;
    return upleft[index];
    break;     
  default:
    break;
  }

  
}

void change_dir(Sprite *sprite,enum Direction direction){

  switch (direction)
  {
  case Up:
    change_Sprite_Img(sprite, getDB()->images.duck_Up);
    break;
  case Left:
    change_Sprite_Img(sprite, getDB()->images.duck_Left);
    break;
  default:
    break;
  }
}
void update_Duck(Sprite *sprite, uint8_t idx) {
  enum Direction direction;
  if (sprite->y == 0) {
    getDB()->sprites->ducks[idx] = NULL; 
    destroy_sprite(sprite);
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
          direction = generaterandomdir(sprite->direction);
          change_dir(sprite,direction);
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
      sprite->y = sprite->y + 10;
    }
    else       sprite->state = Dead;
    }  
}
