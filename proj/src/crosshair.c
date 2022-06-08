#include "Include/crosshair.h"

void update_mouse(struct packet pp, Database *db) {

  if (pp.delta_x != 0 || pp.delta_y != 0) {

    if (db->sprites->crosshair->x + pp.delta_x > 0 && ((db->sprites->crosshair->x + db->sprites->crosshair->width) + pp.delta_x  <= get_h_res())) db->sprites->crosshair->x += pp.delta_x;
    if (db->sprites->crosshair->y - pp.delta_y > 0 && ((db->sprites->crosshair->y + db->sprites->crosshair->height)  - pp.delta_y <= get_v_res())) db->sprites->crosshair->y -= pp.delta_y;
  }

  if (pp.lb) {
    isMouseLBpressed = true;
  }
}


