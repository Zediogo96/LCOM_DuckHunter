#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


/**
 * Subscribe to keyboard interrupts
 * @param bit_no
 */
int kbd_subscribe_int(uint8_t *bit_no);

/**
 * Unsubscribe keyboard interrupts 
 */
int kbd_unsubscribe_int();

#endif /* _KEYBOARD_H_ */
