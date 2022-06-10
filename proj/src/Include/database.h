#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <lcom/lcf.h>

#include "Sprite.h"
#include "kbc.h"
#include "video_gr.h"

#include "../images/background.xpm"
#include "../images/background_night.xpm"
#include "../images/crosshair.xpm"

#include "../images/Duck_Images/duck_Left.xpm"
#include "../images/Duck_Images/duck_Right.xpm"

#include "../images/Duck_Images/duck_Up_Left.xpm"
#include "../images/Duck_Images/duck_Up_Right.xpm"

#include "../images/Duck_Images/duck_Falling.xpm"
#include "../images/Duck_Images/duck_Shot.xpm"
#include "../images/Duck_Images/duck_Up.xpm"

#include "../images/score.xpm"

#include "../images/heart_depleted.xpm"
#include "../images/heart_full.xpm"

#include "../images/Numbers/eight.xpm"
#include "../images/Numbers/five.xpm"
#include "../images/Numbers/four.xpm"
#include "../images/Numbers/nine.xpm"
#include "../images/Numbers/one.xpm"
#include "../images/Numbers/seven.xpm"
#include "../images/Numbers/six.xpm"
#include "../images/Numbers/three.xpm"
#include "../images/Numbers/two.xpm"
#include "../images/Numbers/zero.xpm"
#include "../images/lives.xpm"

#include "../images/Menu/exit.xpm"
#include "../images/Menu/gameOver.xpm"
#include "../images/Menu/gameOver_text.xpm"
#include "../images/Menu/main_menu.xpm"
#include "../images/Menu/pause.xpm"
#include "../images/Menu/rules.xpm"
#include "../images/Menu/rules_text.xpm"
#include "../images/Menu/start.xpm"

#define TOTAL_NR_OF_DUCKS 10
#define GAME_INIT_LIVES 3

/**
 * @brief enum to encapsulate all the possible states of the program
 *
 */
enum CurrentState {
  Menu,
  Menu_Rules,
  GamePlaying,
  GamePaused,
  GameOver,
  Exit
};

/**
 * @brief Struct that encapsulates sprites used by the game
 *
 */
typedef struct
{
  Sprite *crosshair;
  Sprite **ducks;
} Sprites;

/**
 * @brief Struct with all the xpm_images used by the game
 *
 */
typedef struct
{
  xpm_image_t duck_Left, duck_Right, duck_Up_Right, duck_Up_Left, duck_Up,
    duck_Shot, duck_Falling, background, background_night,
    crosshair, scoreBoard,
    zero, one, two, three, four, five, six, seven, eight, nine,
    heart_full, heart_dep,
    main_menu, start, rules, rules_text, exit, pause, gameOver, gameOver_text;
} GameImages;

/**
 * @brief Struct that encapsulates all the necessary information to be used by the program
 *
 */
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

/**
 * @brief Initializes all the game variables to it's default (starting) values
 *
 */
void gameInit();

/**
 * @brief Auxiliar function used to reset some of the game variables to it's default (starting values)
 *
 */
void gameReset();

/**
 * @brief Auxiliar function to free memory allocated for the game
 *
 */
void gameDestroy();

/**
 * @brief Create a Crosshair sprite object
 *
 */
void createCrosshair();

/**
 * @brief Create a Ducks Array object
 *
 */
void createDucksArray();

/**
 * @brief Create a Duck object
 *
 */
void create_Duck();

/**
 * @brief Function that encapsulates all the functions needs to draw the main menu
 *
 */
void drawMainMenu();

/**
 * @brief Draws the background image according to the hours and minutes read from the RTC
 *
 * @param h hours
 * @param m minutes
 */
void drawBackground(uint32_t h, uint32_t m);

/**
 * @brief Draws the crosshair sprite
 *
 */
void drawCrosshair();

/**
 * @brief Function that is used to draw the full hearts or depleted hearts, based on the current number of lives
 *
 */
void drawLives();

/**
 * @brief Function used to draw a xpm_image based on the number it's given
 *
 * @param number
 * @param x_pos
 * @param y_pos
 */
void drawNumber(int number, uint16_t x_pos, uint16_t y_pos);

/**
 * @brief Function that used to draw all the score digits 
 *
 */
void drawScoreDigits();

/**
 * @brief Function that encapsulates all the other functions needed to draw the score
 * 
 */
void draw_fullScore();

/**
 * @brief Function that encapsulates all the other functions needed to draw the lives board
 * 
 */
void draw_fullLives();

/**
 * @brief Function that draws all the duck sprites from the duck array
 * 
 */
void draw_ducks();

/**
 * @brief Function that is used to process the current Select in the Menu, based on the value of the out_byte it receives
 * 
 * @param out_b out_byte
 */
void updateCurrentSelect(uint8_t out_b);

/**
 * @brief Function that is used to process the pause feature, that means if the P key is pressed in-game
 * 
 * @param out_b 
 */
void handlePause(uint8_t out_b);

/**
 * @brief Draws the paused image
 * 
 */
void drawPausedIndicator();

#endif // _DATABASE_H_
