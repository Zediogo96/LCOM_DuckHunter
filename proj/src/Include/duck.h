#ifndef _DUCK_H_
#define _DUCK_H_

#include "database.h"

/**
 * @brief Function to encapsulate the update of every duck position, state and direction, that is currently allocated in the game,
 * using the update_Duck() function
 */
void update_ducks_status();

/**
 * @brief Function to encapsulate the try to give the duck a random direction if given conditions are met.
 */
void update_ducks_dir();

/**
 * @brief Updates the duck position, state and direction
 * 
 * @param sprite pointer of type Sprite
 * @param idx index of the Sprite in the ducks array
 */
void update_Duck(Sprite *sprite, uint8_t idx);

/**
 * @brief Auxiliar function used to create a new random direction to the duck given it's current position
 * 
 * @param direction current direction of the duck
 * @return enum Direction new direction for the duck to be update into
 */
enum Direction generate_random_dir(enum Direction direction);

/**
 * @brief Function used to update a sprite image and position
 * 
 * @param sprite 
 * @param direction 
 */
void change_dir(Sprite *sprite,enum Direction direction);

/**
 * @brief Auxiliar function used to update a sprite direction given the random direction that it gets from generate_random_dir
 * 
 * @param sprite 
 */
void update_direction(Sprite *sprite);

#endif
