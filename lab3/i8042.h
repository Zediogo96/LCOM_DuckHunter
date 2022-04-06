#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8254 i8254
 * @{
 *
 * Constants for programming the i8254 Timer. Needs to be completed.
 *
 */

uint64_t no_interrupts;

uint32_t timer_counter;

/** 
 * 
 * Bits 7 and 6 signal an error in the (serial)
 *  communication between the keyboard and the KBC
 * 
 **/

#define KBD_IRQ 1 /* IRQ for KEYBOARD */
#define KBD_BREAKCODE_ESQ 0x81 /* BREAK CODE FOR THE ESCAPE KEY */
#define DELAY_US 20000
#define KBD_OUTPUT_BUF 0x60 

#define KBD_READ_CMD 0x20 /* KBC READ COMMAND */
#define KBD_WRITE_CMD 0x60 /*  KBC WRITE COMMAND */
#define KBD_STATUS_REG 0x64 /* KBC STATUS REGISTER */
#define KBD_CMD_REG 0x64 /* KBC COMMAND REGISTER */

#define KBD_PARITY_ERROR BIT(7) 
#define KBD_TIMEOUT_ERROR BIT(6)

/** BIT 5,4,3,2 não são necessários segundo o prof para LCOM **/

/** if bit 1, the IBF, is set, do not write to the IN_BUF,
 *  i.e. to both both ports 0x60 and 0x64. **/

#define KBD_INPUT_BUFFER_FULL BIT(1) 
#define KBD_OUTPUT_BUFFER_FULL BIT(0)

#endif /* _LCOM_I8254_H */

