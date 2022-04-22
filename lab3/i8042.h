#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KBD_IRQ 1 /* IRQ for keyboard */
#define KBD_ESC_BREAKCODE 0x81 

#define KBD_STATUS_REG 0x64

#define KBD_OUTPUT_BUFFER_FULL BIT(0)
#define KBD_OUTPUT_BUF 0x60

#define KBD_PARITY_ERROR BIT(7)
#define KBD_TIMEOUT_ERROR BIT(6)