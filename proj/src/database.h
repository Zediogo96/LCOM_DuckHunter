#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <lcom/lcf.h>

#include "Sprite.h"
#include "video_gr.h"

#include "images/background.xpm"
#include "images/crosshair.xpm"

#include "images/Duck_Images/duck_Left.xpm"
#include "images/Duck_Images/duck_Right.xpm"

#include "images/Duck_Images/duck_Up_Right.xpm"
#include "images/Duck_Images/duck_Up_Left.xpm"

#include "images/Duck_Images/duck_Up.xpm"
#include "images/Duck_Images/duck_Shot.xpm"
#include "images/Duck_Images/duck_Falling.xpm"

#include "images/score.xpm"

#include "images/lives.xpm"
#include "images/Numbers/eight.xpm"

#define TOTAL_NR_OF_DUCKS 10



typedef struct
{
  Sprite *crosshair;
  Sprite **ducks;
} Sprites;

typedef struct
{
  xpm_image_t duck_Left, duck_Right, duck_Up_Right, duck_Up_Left, duck_Up,
   duck_Shot, duck_Falling, background, crosshair, scoreBoard, lives, eight;
} GameImages;

typedef struct
{
  GameImages images;
  Sprites *sprites;
  int score;
} Database;

/**
 * @brief To facilitate using db in another file (note that it's static)
 */
Database *getDB();

/**
 * @brief Method that will be used to load all xpm's necessary to the game to a single struct,
 * which makes it easier to access those images when needed.
 */
void loadAllXPMs();

void drawBackground();

void drawCrosshair();

void drawLives();

void drawScoreBoard();

void drawNumbers();

void draw_ducks();

void drawDuck(Sprite * sprite);

#endif // _DATABASE_H_
