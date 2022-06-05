#include "Include/database.h"

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
  xpm_load(heart_dep_xpm, XPM_8_8_8_8, &db->images.heart_dep);
  xpm_load(heart_full_xpm, XPM_8_8_8_8, &db->images.heart_full);

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

  /** MENUS RELATED **/
  xpm_load(main_menu_xpm, XPM_8_8_8_8, &db->images.main_menu);
  xpm_load(start_xpm, XPM_8_8_8_8, &db->images.start);
  xpm_load(rules_xpm, XPM_8_8_8_8, &db->images.rules);
  xpm_load(exit_xpm, XPM_8_8_8_8, &db->images.exit);
}

Database *getDB() {
  return db;
}

void drawMainMenu() {

  vg_draw_image(db->images.main_menu, 0, 0);

  vg_draw_image(db->images.duck_Shot, 120, 500);
  vg_draw_image(db->images.crosshair, 100, 470);

  vg_draw_image(db->images.duck_Up_Right, 840, 530);
  vg_draw_image(db->images.duck_Up_Right, 920, 590);

  vg_draw_rectangle(460, 490, 200, 70, (db->currentSelect == 0) ? 0x746AB0 : 0x008b8b);
  vg_draw_image(db->images.start, 467, 495);

  vg_draw_rectangle(460, 590, 200, 70, (db->currentSelect == 1) ? 0x746AB0 : 0x008b8b);
  vg_draw_image(db->images.rules, 465, 595);

  vg_draw_rectangle(460, 690, 200, 70, (db->currentSelect == 2) ? 0x746AB0 : 0x008b8b);

  vg_draw_image(db->images.exit, 465, 695);
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

void drawScoreDigits() {

  uint16_t x_pos = 1050;

  int tmp = getDB()->score;
  uint8_t idx = 0;

  if (tmp == 0) {
    drawNumber(0, x_pos, 790);
  }
  else {
    while (tmp != 0) {
      uint8_t digit = tmp % 10;
      tmp /= 10;
      drawNumber(digit, x_pos - idx, 790);
      idx += 20;
    }
  }
}

void draw_fullScore() {
  drawScoreBoard();
  drawScoreDigits();
}

void draw_fullLives() {
  vg_draw_rectangle(50, 780, 190, 60, 0x000000);
  vg_draw_hline(49, 779, 190, 0xFFFFFF);
  vg_draw_hline(49, 839, 190, 0xFFFFFF);
  vg_draw_vline(49, 779, 60, 0xFFFFFF);
  vg_draw_vline(239, 779, 60, 0xFFFFFF);
  drawLives();
}

// Update logic here to draw only number of lives left
void drawLives() {
  uint16_t x_pos = 70;
  uint8_t idx = 0;
  uint8_t start_lives = GAME_INIT_LIVES;
  for (uint8_t i = 0; i < start_lives; ++i) {
    if (i < getDB()->lives) {
      vg_draw_image(db->images.heart_full, x_pos + idx, 790);
    }
    else {
      vg_draw_image(db->images.heart_dep, x_pos + idx, 790);
    }

    idx += 50;
  }
}

void drawNumber(int number, uint16_t x_pos, uint16_t y_pos) {
  switch (number) {
    case 0:
      vg_draw_image(db->images.zero, x_pos, y_pos);
      break;
    case 1:
      vg_draw_image(db->images.one, x_pos, y_pos);
      break;
    case 2:
      vg_draw_image(db->images.two, x_pos, y_pos);
      break;

    case 3:
      vg_draw_image(db->images.three, x_pos, y_pos);
      break;

    case 4:
      vg_draw_image(db->images.four, x_pos, y_pos);
      break;

    case 5:
      vg_draw_image(db->images.five, x_pos, y_pos);
      break;

    case 6:
      vg_draw_image(db->images.six, x_pos, y_pos);
      break;

    case 7:
      vg_draw_image(db->images.seven, x_pos, y_pos);
      break;

    case 8:
      vg_draw_image(db->images.eight, x_pos, y_pos);
      break;

    case 9:
      vg_draw_image(db->images.nine, x_pos, y_pos);
      break;
  }
}

void draw_ducks() {

  for (int i = 0; i < TOTAL_NR_OF_DUCKS; ++i) {
    if (getDB()->sprites->ducks[i] != NULL) {
      draw_sprite(getDB()->sprites->ducks[i]);
    }
  }
}

void updateCurrentSelect(uint8_t out_b) {

  switch (out_b) {
    case 0xd0: // DOWN
      if (db->currentSelect == 2)
        db->currentSelect = 0;
      else
        db->currentSelect++;
      break;
    case 0xc8: // UP
      if (db->currentSelect == 0)
        db->currentSelect = 2;
      else
        db->currentSelect--;
      break;
    case 0x9c: // ENTER
      switch (db->currentSelect) {
        case 0:
          db->currentState = GamePlaying;
          break;
        case 1:
          break;
        case 2:
          db->currentState = Exit;
          break;
        default: break;
      }
    default: break;
  }
}
