#ifndef _HITBOXES_H_
#define _HITBOXES_H_

#include "crosshair.h"

extern bool isMouseLBpressed;

/**
 * @brief Auxiliar function that checks if it occurs a collision between the center of the sprite 1 and sprite 2.
 * Calculates sprite1 center position (x & y) and checks if that position is within the sprite 2 borders.
 *
 * @param sprite1
 * @param sprite2
 * @return true if collision occurs
 * @return false
 */
bool checkHitboxCollision(Sprite *sprite1, Sprite *sprite2);

/**
 * @brief Function to check for every duck if they collided with the center of crosshair (sprite1) while mouse Left Button was pressed.
 * If the collision happens, updates their state and direction, while also increases the score of the game.
 *
 * @param sprite1 (duck)
 * @return true
 * @return false
 */
bool checkDuckGotShot(Sprite *sprite1);

#endif // _HITBOXES_H
