#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <lcom/lcf.h>

#include "Sprite.h"
#include "video_gr.h"
#include "keyboard.h"

#include "../images/background.xpm"
#include "../images/background_night.xpm"
#include "../images/crosshair.xpm"

#include "../images/Duck_Images/duck_Left.xpm"
#include "../images/Duck_Images/duck_Right.xpm"

#include "../images/Duck_Images/duck_Up_Right.xpm"
#include "../images/Duck_Images/duck_Up_Left.xpm"

#include "../images/Duck_Images/duck_Up.xpm"
#include "../images/Duck_Images/duck_Shot.xpm"
#include "../images/Duck_Images/duck_Falling.xpm"

#include "../images/score.xpm"

#include "../images/heart_depleted.xpm"
#include "../images/heart_full.xpm"

#include "../images/lives.xpm"
#include "../images/Numbers/zero.xpm"
#include "../images/Numbers/one.xpm"
#include "../images/Numbers/two.xpm"
#include "../images/Numbers/three.xpm"
#include "../images/Numbers/four.xpm"
#include "../images/Numbers/five.xpm"
#include "../images/Numbers/six.xpm"
#include "../images/Numbers/seven.xpm"
#include "../images/Numbers/eight.xpm"
#include "../images/Numbers/nine.xpm"

#include "../images/Menu/main_menu.xpm"
#include "../images/Menu/start.xpm"
#include "../images/Menu/rules.xpm"
#include "../images/Menu/rules_text.xpm"
#include "../images/Menu/exit.xpm"
#include "../images/Menu/pause.xpm"
#include "../images/Menu/gameOver.xpm"
#include "../images/Menu/gameOver_text.xpm"

#define TOTAL_NR_OF_DUCKS 10
#define GAME_INIT_LIVES 3

enum CurrentState {
        Menu,
        Menu_Rules,
        GamePlaying,
        GamePaused,
        GameOver,
        Exit
};

typedef struct
{
  Sprite *crosshair;
  Sprite **ducks;
} Sprites;

typedef struct
{
  xpm_image_t duck_Left, duck_Right, duck_Up_Right, duck_Up_Left, duck_Up,
   duck_Shot, duck_Falling, background, background_night,
   crosshair, scoreBoard,
   zero, one, two, three, four, five, six, seven, eight, nine,
   heart_full, heart_dep,
   main_menu, start, rules, rules_text, exit, pause, gameOver, gameOver_text;
} GameImages;

typedef struct
{
  GameImages images;
  Sprites *sprites;
  uint16_t score;
  uint8_t ghostScore;
  uint8_t lives;
  uint8_t gameSpeed;
  enum CurrentState currentState;
  uint8_t currentSelect;
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

void gameInit();

void gameReset();

void gameDestroy();

void createCrosshair();

void createDucksArray();

void create_Duck();

void drawMainMenu();

void drawBackground(uint32_t h, uint32_t m);

void drawCrosshair();

void drawLives();

void drawScoreBoard();

void drawNumber(int number, uint16_t x_pos, uint16_t y_pos);

void drawScoreDigits();

void draw_fullScore();

void draw_fullLives();

void draw_ducks();

void drawDuck(Sprite * sprite);

void updateCurrentSelect(uint8_t out_b);

void handlePause(uint8_t out_b);

void drawPausedIndicator();

#endif // _DATABASE_H_
