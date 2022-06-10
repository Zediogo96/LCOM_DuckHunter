#ifndef __MOUSE_H_
#define __MOUSE_H_

#include "i8042.h"
#include "kbc.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define MOUSE_LB_CLICK BIT(0)
#define MOUSE_RB_CLICK BIT(1)
#define MOUSE_MB_CLICK BIT(2)

#define MOUSE_X_SIGN BIT(4)
#define MOUSE_Y_SIGN BIT(5)

#define MOUSE_X_OVFL BIT(6)
#define MOUSE_Y_OVFL BIT(7)

/**
 * @brief Function used to subscribe mouse interrupts
 *
 * @param bit_no BIT number
 * @return 0 if successful, 1 otherwise
 */
int mouse_subscribe_int(uint8_t *bit_no);

/**
 * @brief Function used to unsubscribe mouse interrupts
 *
 * @return 0 if successful, 1 otherwise
 */
int mouse_unsubscribe_int();

/**
 * @brief Function used to process information read from the the KBC out byte into a (mouse) packet.
 * Packets are used to store information like mouse x_pos / y_pos / it's displacement / etc.
 *
 * @param bytes
 * @return struct packet
 */
struct packet process_packets(uint8_t *bytes);

/**
 * @brief Function to disable mouse data reporting
 *
 * @return 0 if successful, 1 otherwise
 */
int mouse_disable_reporting();

#endif
