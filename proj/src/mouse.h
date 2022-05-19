#ifndef __MOUSE_H_
#define __MOUSE_H_

#include "i8042.h"
#include "kbc.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int mouse_subscribe_int(uint8_t *bit_no);

int mouse_unsubscribe_int();

struct packet process_packets(uint8_t *bytes);

int mouse_disable_reporting();

#define MOUSE_LB_CLICK BIT(0)
#define MOUSE_RB_CLICK BIT(1)
#define MOUSE_MB_CLICK BIT(2)

#define MOUSE_X_SIGN BIT(4)
#define MOUSE_Y_SIGN BIT(5)

#define MOUSE_X_OVFL BIT(6)
#define MOUSE_Y_OVFL BIT(7)



#endif
