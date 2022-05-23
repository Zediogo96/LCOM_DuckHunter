#include "duck.h"
#include "database.h"

void create_Duck(Database *db) {
  db->sprites->duck = create_sprite(db->images.duck_Up, 600, 200, 1, 1, Up, Alive);
}

void update_Duck(Sprite *sprite) {
  if (sprite->state == Dead) {
    change_Sprite_Img(sprite, getDB()->images.duck_Falling);
    sprite->state = Falling;
  }

  if (sprite->state == Falling) {
    if (sprite->y < 600) {
      sprite->y = sprite->y + 5;
    }
    else {
      free(sprite);
    }
  }
}
