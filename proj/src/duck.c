#include "Include/duck.h"
#include "Include/database.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void update_ducks_status() {
  for (int i = 0; i < TOTAL_NR_OF_DUCKS; ++i) {
    if (getDB()->sprites->ducks[i] != NULL) {
      update_Duck(getDB()->sprites->ducks[i], i);
    }
  }
}
void update_ducks_dir() {
  for (int i = 0; i < TOTAL_NR_OF_DUCKS; ++i) {
    if (getDB()->sprites->ducks[i] != NULL) {
      update_direction(getDB()->sprites->ducks[i]);
    }
  }
}
enum Direction generate_random_dir(enum Direction direction) {
  srand(time(NULL));
  int index = rand() % 8;
  enum Direction up[] = {Right, Left, Up_Right, Up_Left, Up};
  enum Direction right[] = {Right, Up_Right};
  enum Direction left[] = {Left, Up_Left};
  enum Direction upright[] = {Up_Right, Right, Up};
  enum Direction upleft[] = {Left, Up_Left, Up};

  switch (direction) {
    case Up:
      index = rand() % 5;
      return up[index];
      break;
    case Right:
      index = rand() % 2;
      return right[index];
      break;
    case Left:
      index = rand() % 2;
      return left[index];
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

  return direction;
}

void change_dir(Sprite *sprite, enum Direction direction) {

  uint8_t speed = getDB()->gameSpeed;

  switch (direction) {
    case Up:
      change_Sprite_Img(sprite, getDB()->images.duck_Up);
      sprite->y -= speed;
      break;
    case Left:
      change_Sprite_Img(sprite, getDB()->images.duck_Left);
      sprite->x -= speed;
      break;
    case Right:
      change_Sprite_Img(sprite, getDB()->images.duck_Right);
      sprite->x += speed;
      break;
    case Up_Left:
      change_Sprite_Img(sprite, getDB()->images.duck_Up_Left);
      sprite->x -= speed;
      sprite->y -= speed;
      break;
    case Up_Right:
      change_Sprite_Img(sprite, getDB()->images.duck_Up_Right);
      sprite->x += speed;
      sprite->y -= speed;
      break;
    default:
      break;
  }
}
void update_direction(Sprite *sprite) {
  enum Direction direction;
  uint8_t speed = getDB()->gameSpeed;
  if (sprite->state == Alive) {

    switch (sprite->direction) {
      case Up:
        if (sprite->y > 550)
          sprite->y -= speed;
        else {
          direction = generate_random_dir(sprite->direction);
          change_dir(sprite, direction);
          sprite->direction = direction;
        }
        break;
      case Left:

        if (sprite->x > 1) {
          direction = generate_random_dir(sprite->direction);
          change_dir(sprite, direction);
          sprite->direction = direction;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Right);
          sprite->direction = Up_Right;
        }
        break;
      case Right:

        if ((sprite->x + sprite->width + speed) <= get_h_res()) {
          direction = generate_random_dir(sprite->direction);
          change_dir(sprite, direction);
          sprite->direction = direction;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Left);
          sprite->direction = Up_Left;
        }
        break;

      case Up_Left:
        if ((sprite->x + speed> 0) && (sprite->y + speed > 0)) {
          direction = generate_random_dir(sprite->direction);
          change_dir(sprite, direction);
          sprite->direction = direction;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Right);
          sprite->direction = Up_Right;
        }
        break;

      case Up_Right:
        if ((sprite->x + sprite->width + speed) <= get_h_res() && (sprite->y + speed > 0)) {
          direction = generate_random_dir(sprite->direction);
          change_dir(sprite, direction);
          sprite->direction = direction;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Left);
          sprite->direction = Up_Left;
        }
        break;

      default:
        break;
    }
  }
}
void update_Duck(Sprite *sprite, uint8_t idx) {

  uint8_t speed = getDB()->gameSpeed;

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
        sprite->y -= speed;

        break;
      case Right:

        if ((sprite->x + sprite->width + speed) <= get_h_res()) {
          sprite->x += speed;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Left);
          sprite->direction = Up_Left;
        }
        break;
      case Left:
        if (sprite->x > 1) {
          sprite->x -= speed;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Right);
          sprite->direction = Up_Right;
        }
        break;
      case Up_Left:
        if ((sprite->x - speed > 0) && (sprite->y + speed > 0)) {
          sprite->x -= speed;
          sprite->y -= speed;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Right);
          sprite->direction = Up_Right;
        }

        break;
      case Up_Right:
        if ((sprite->x + sprite->width + speed) <= get_h_res() && (sprite->y + speed > 0)) {
          sprite->x += speed;
          sprite->y -= speed;
        }
        else {
          change_Sprite_Img(sprite, getDB()->images.duck_Up_Left);
          sprite->direction = Up_Left;
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
    else
      sprite->state = Dead;
  }
}
