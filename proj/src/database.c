#include "database.h"

static Database *db;

void loadAllXPMs() {
  db = (Database *) malloc(sizeof(Database));
  db->sprites = (Sprites*)malloc(sizeof(Sprites));

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
}

Database *getDB() {
  return db;
}

void drawBackground() {
  vg_draw_image(db->images.background, 0, 0);
}

void drawCrosshair() {
  draw_sprite(db->sprites->crosshair, get_video_mem());
}

void drawDuck() {

  /** SWITCH CASE PARA VARIAR A SPRITE SEGUNDO A DIREÇÃO????????????? **/

  draw_sprite(db->sprites->duck, get_video_mem());


}
