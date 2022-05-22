#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <lcom/lcf.h>

#include "video_gr.h"
#include "Sprite.h"

#include "images/background.xpm"
#include "images/crosshair.xpm"
#include "images/ducks.xpm"

typedef struct 
{
  Sprite *crosshair;
  uint8_t temporario;
} Sprites;

typedef struct
{
  xpm_image_t ducks, background, crosshair;
} GameImages;

typedef struct
{
  GameImages images;
  Sprites * sprites;
  int score;
} Database;

/**
 * @brief To facilitate using db in another file (note that it's static)
 */
Database * getDB();

/**
 * @brief Method that will be used to load all xpm's necessary to the game to a single struct,
 * which makes it easier to access those images when needed.
 */
void loadAllXPMs();

void drawBackground();

void drawCrosshair();

#endif // _DATABASE_H_
