#ifndef _HITBOXES_H_
#define _HITBOXES_H_

#include "crosshair.h"

extern bool isMouseLBpressed;

bool checkHitboxCollision(Sprite * sprite1, Sprite * sprite2);

bool checkDuckGotShot(Sprite* sprite1);





#endif // _HITBOXES_H
