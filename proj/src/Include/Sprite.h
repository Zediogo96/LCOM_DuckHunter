#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "video_gr.h"

/**
 * @brief enum to encapsulate all possible directions of the Sprite
 *
 */
enum Direction { Right,
                 Left,
                 Up_Right,
                 Up_Left,
                 Up,
                 Down,
                 default_Dir };

/**
 * @brief enum to encapsulate all possible states of the Sprite
 *
 */
enum State { Dead,
             Alive,
             Shot,
             Falling,
             default_State };

/**
 * @brief Struct to keep all the relevant information of an Sprite.
 */
typedef struct {
  int x, y;           // current position
  int width, height;  // dimensions
  int xspeed, yspeed; // current speed
  uint8_t *map;       // the pixmap
  enum Direction direction;
  enum State state;
} Sprite;

/**
 * @brief Create a sprite object, allocating all the necessary memory
 *
 * @param img xpm_image
 * @param x x coordinate of the sprite
 * @param y y coordinate of the sprite
 * @param xspeed Speed of the x axis
 * @param yspeed Speed of the y axis
 * @param direction
 * @param state
 * @return Sprite*
 */
Sprite *create_sprite(xpm_image_t img, int x, int y, int xspeed, int yspeed, enum Direction direction, enum State state);

/**
 * @brief Deletes the sprite, freeing all the memory that was allocated for it
 *
 * @param sp Pointer of type Sprite
 */
void destroy_sprite(Sprite *sp);

/**
 * @brief Draws the sprite to the double buffer
 *
 * @param sp Pointer of type Sprite
 * @return 0 if sucessful, 1 otherwise
 */
int draw_sprite(Sprite *sp);

/**
 * @brief Auxiliar function used to change the current sprite image
 *
 * @param sprite Pointer of type sprite image
 * @param img xpm_image_t to be updated into
 */
void change_Sprite_Img(Sprite *sprite, xpm_image_t img);

#endif // _SPRITE_H
