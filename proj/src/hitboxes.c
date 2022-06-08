#include "Include/hitboxes.h"
#include "Include/database.h"

bool checkHitboxCollision(Sprite *sprite1, Sprite *sprite2) {

  uint16_t half_x = sprite1->width / 2;
  uint16_t half_y = sprite1->height / 2;

  if (sprite2->x <= sprite1->x + half_x && sprite2->x >= sprite1->x - half_x && sprite2->y <= sprite1->y + half_y && sprite2->y >= sprite1->y - half_y) return true;

  return false;
}

bool checkDuckGotShot(Sprite *sprite1) {

  for (int i = 0; i < TOTAL_NR_OF_DUCKS; i++) {
    if (getDB()->sprites->ducks[i] != NULL && getDB()->sprites->ducks[i]->state == Alive) {
      if (checkHitboxCollision(sprite1, getDB()->sprites->ducks[i]) && isMouseLBpressed) {
        change_Sprite_Img(getDB()->sprites->ducks[i], getDB()->images.duck_Shot);

        getDB()->sprites->ducks[i]->state = Shot;
        getDB()->sprites->ducks[i]->direction = Down;
        getDB()->score += 10;
        getDB()->ghostScore += 10;
      }
    }
  }

  isMouseLBpressed = false;

  return false;
}
