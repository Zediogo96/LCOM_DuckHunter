#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

#include <lcom/lcf.h>

#include "database.h"
#include "video_gr.h"
#include "Sprite.h"

#include <stdio.h>

void update_mouse(struct packet pp, Database *db);

void createCrosshair(Database* db);

#endif // CROSSHAIR
