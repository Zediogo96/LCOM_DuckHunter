#ifndef __KBC_H_
#define __KBC_H_

#include "Include/i8042.h"

/** BREAKCODES TO BE USED BY THE PROGRAM **/
#define KBD_BREAKCODE_ESC 0x81
#define KBD_BREAKCODE_ARROW_DOWN 0xD0
#define KBD_BREAKCODE_ARROW_UP 0xC8
#define KBD_BREAKCODE_ENTER 0x9C
#define KBD_BREAKCODE_P 0x99
#define KBD_BREAKCODE_R 0x93

/**
 * @brief Function to subscribe the kbc interrupts on exclusive mode
 *
 * @param bit_no Bit Number
 * @return 0 if sucessful, otherwise 1
 */
int kbc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes the kbc interrupts
 *
 * @return 0 if sucessful, otherwise 1
 */
int kbc_unsubscribe_int();

/**
 * @brief Function to issue an command to a specific port
 *
 * @param cmd command
 * @param port
 * @return 0 if it was sucessful, 1 if not.
 */
int kbc_issue_command(uint8_t cmd, int port);

/**
 * @brief Function to read the data from the KBC and pass it to the OUT BYTE.
 * Checks if the input is full before reading, if it reads it reads to DATA.
 * After it checks if there were any parity or timeout errors, if not passes the data
 * information to the OUT_BYTE
 *
 * @return 0 if it was sucessful, 1 if not.
 */
int kbc_read_outb();

/**
 * @brief Function to check if there was any informationr read to the OUT BYTE.
 * If not waits for a specified time before trying to read again.
 */
void(kbc_ih)();

#endif /* _KEYBOARD_H_ */
