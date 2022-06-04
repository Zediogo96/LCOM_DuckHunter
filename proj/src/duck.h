#ifndef _DUCK_H_
#define _DUCK_H_

#include "database.h"

void createDucksArray();

void create_Duck();

void update_ducks();

void update_Duck(Sprite *sprite, uint8_t idx);

enum Direction generaterandomdir(enum Direction direction);

void change_dir(Sprite *sprite,enum Direction direction);

#endif
