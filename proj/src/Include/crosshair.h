#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

#include <lcom/lcf.h>

#include "Sprite.h"
#include "database.h"
#include "video_gr.h"

#include <stdio.h>

bool isMouseLBpressed;

/**
 * @brief Updates crosshair sprite x and y position based on information received from mouse interrupts packets.
 *
 * @param pp Mouse Packet
 * @param db Central Database
 */
void update_mouse(struct packet pp, Database *db);

#endif // CROSSHAIR
