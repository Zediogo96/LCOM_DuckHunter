#include "crosshair.h"

void update_mouse(struct packet pp, Database *db) {

  if (pp.delta_x != 0 || pp.delta_y != 0) {
    db->sprites->crosshair->x += pp.delta_x;
    db->sprites->crosshair->y -= pp.delta_y;
  }
}

void createCrosshair(Database *db) {
  db->sprites->crosshair = create_sprite(db->images.crosshair, 300, 300, 1, 1);
}
