#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "Include/i8042.h"

/**
 * Subscribe to keyboard interrupts
 * @param bit_no
 */
int kbd_subscribe_int(uint8_t *bit_no);

/**
 * Unsubscribe keyboard interrupts 
 */
int kbd_unsubscribe_int();

int kbc_issue_command(uint8_t cmd, int port);

void kbc_poll();

int kbc_read_outb();

void(kbc_ih)();

#endif /* _KEYBOARD_H_ */
