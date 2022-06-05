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
 * @brief FOR MOUSE OPERATIONS
**/

#define MOUSE_IRQ 12 /**< Mouse IRQ line */

#define DATA_PACKET_BYTES 3

#define WRITE_BYTE_TO_MOUSE 0xD4
#define ENABLE_MOUSE_DATA_REPORTING 0xF4
#define DISABLE_MOUSE_DATA_REPORTING 0xF5


#define DISABLE_MOUSE 0xA7
#define ENABLE_MOUSE 0XA8
#define DISABLE_DATA_REPORTING 0xF5
#define ENABLE_DATA_REPORTING 0xF4
#define READ_DATA 0xEB
#define SET_STREAM_MODE 0xEA
#define SET_DEFAULT 0xF6

#define ACK 0xFA /* if everything OK */
#define NACK 0xFE /* if invalid byte (may be due to a serial communication error */
#define ERROR 0xFC /* second consecutive invalid byte */

/** 
 * 
 * Bits 7 and 6 signal an error in the (serial)
 *  communication between the keyboard and the KBC
 * 
 **/

#define KBD_IRQ 1 /* IRQ for KEYBOARD */
#define KBD_BREAKCODE_ESC 0x81 /* BREAK CODE FOR THE ESCAPE KEY */
#define DELAY_US 20000
#define KBC_OUTPUT_BUF 0x60 

#define KBC_READ_CMD 0x20 /* KBC READ COMMAND */
#define KBC_WRITE_CMD 0x60 /*  KBC WRITE COMMAND */
#define KBC_STATUS_REG 0x64 /* KBC STATUS REGISTER */
#define KBC_CMD_REG 0x64 /* KBC COMMAND REGISTER */

#define KBD_PARITY_ERROR BIT(7) 
#define KBD_TIMEOUT_ERROR BIT(6)

/** BIT 5,4,3,2 não são necessários segundo o prof para LCOM **/

/** if bit 1, the IBF, is set, do not write to the IN_BUF,
 *  i.e. to both both ports 0x60 and 0x64. **/

#define KBD_INPUT_BUFFER_FULL BIT(1) 
#define KBD_OUTPUT_BUFFER_FULL BIT(0)

#endif /* _LCOM_I8254_H */

