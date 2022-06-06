#ifndef _DUCK_H_
#define _DUCK_H_

#include "database.h"

void update_ducks_status();

void update_ducks_dir();

void update_Duck(Sprite *sprite, uint8_t idx);

enum Direction generaterandomdir(enum Direction direction);

void change_dir(Sprite *sprite,enum Direction direction);

void update_direction(Sprite *sprite);

#endif
