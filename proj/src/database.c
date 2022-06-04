#include "database.h"

static Database *db;

void loadAllXPMs() {
  db = (Database *) malloc(sizeof(Database));
  db->sprites = (Sprites *) malloc(sizeof(Sprites));

  /** LOADS RELATED TO DUCKS **/
  xpm_load(duck_Left_xpm, XPM_8_8_8_8, &db->images.duck_Left);
  xpm_load(duck_Right_xpm, XPM_8_8_8_8, &db->images.duck_Right);
  xpm_load(duck_Up_Right_xpm, XPM_8_8_8_8, &db->images.duck_Up_Right);
  xpm_load(duck_Up_Left_xpm, XPM_8_8_8_8, &db->images.duck_Up_Left);
  xpm_load(duck_Up_xpm, XPM_8_8_8_8, &db->images.duck_Up);
  xpm_load(duck_Shot_xpm, XPM_8_8_8_8, &db->images.duck_Shot);
  xpm_load(duck_Falling_xpm, XPM_8_8_8_8, &db->images.duck_Falling);

  /** ELSE **/
  xpm_load(background_xpm, XPM_8_8_8_8, &db->images.background);
  xpm_load(crosshair_xpm, XPM_8_8_8_8, &db->images.crosshair);
  xpm_load(score_xpm, XPM_8_8_8_8, &db->images.scoreBoard);
  xpm_load(lives_xpm, XPM_8_8_8_8, &db->images.lives);


  // Numbers for score
  xpm_load(zero_xpm, XPM_8_8_8_8, &db->images.zero);
  xpm_load(one_xpm, XPM_8_8_8_8, &db->images.one);
  xpm_load(two_xpm, XPM_8_8_8_8, &db->images.two);
  xpm_load(three_xpm, XPM_8_8_8_8, &db->images.three);
  xpm_load(four_xpm, XPM_8_8_8_8, &db->images.four);
  xpm_load(five_xpm, XPM_8_8_8_8, &db->images.five);
  xpm_load(six_xpm, XPM_8_8_8_8, &db->images.six);
  xpm_load(seven_xpm, XPM_8_8_8_8, &db->images.seven);
  xpm_load(eight_xpm, XPM_8_8_8_8, &db->images.eight);
  xpm_load(nine_xpm, XPM_8_8_8_8, &db->images.nine);
}

Database *getDB() {
  return db;
}

void drawBackground() {
  vg_draw_image(db->images.background, 0, 0);
}

void drawCrosshair() {
  draw_sprite(db->sprites->crosshair);
}

void drawScoreBoard() {
  vg_draw_image(db->images.scoreBoard, 900, 770);
}

// Update logic here to draw only number of lives left
void drawLives() {
  vg_draw_image(db->images.lives, 80, 790);
}

void drawNumber(int n) {
  vg_draw_image(db->images.eight, 990,790);
}

void draw_ducks() {

  for (int i = 0; i < TOTAL_NR_OF_DUCKS; ++i) {
    if (getDB()->sprites->ducks[i] != NULL) {
      draw_sprite(getDB()->sprites->ducks[i]);
    }
  }
}
