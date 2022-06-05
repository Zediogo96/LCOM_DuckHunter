#include "Include/hitboxes.h"
#include "Include/database.h"

bool checkHitboxCollision(Sprite *sprite1, Sprite *sprite2) {

  if ((sprite1->x + sprite1->width) < sprite2->x || (sprite2->x + sprite2->width) < sprite1->x || (sprite1->y + sprite1->height) < sprite2->y || (sprite2->y + sprite2->height) < sprite1->y)
    return false;
  return true;
}

bool checkDuckGotShot(Sprite *sprite1) {

  for (int i = 0; i < TOTAL_NR_OF_DUCKS; i++) {
    if (getDB()->sprites->ducks[i] != NULL && getDB()->sprites->ducks[i]->state == Alive) {
      if (checkHitboxCollision(sprite1, getDB()->sprites->ducks[i]) && isMouseLBpressed) {
        change_Sprite_Img(getDB()->sprites->ducks[i], getDB()->images.duck_Shot);

        getDB()->sprites->ducks[i]->state = Shot;
        getDB()->sprites->ducks[i]->direction = Down;
        getDB()->score += 10;
      }
    }
  }

  isMouseLBpressed = false;

  return false;
}
