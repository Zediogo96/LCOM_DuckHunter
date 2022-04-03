#ifndef _VAR_H_
#define _VAR_H_
#include <lcom/lcf.h>

//KB registers

#define KBC_ST_REG 0x64
#define KBC_CMD_REG 0x64
#define KB_STATUS_REG 0x64
#define KB_OUT_BUFF 0x60

//KB status byte
#define Parity BIT(7)
#define Timeout BIT(6)
#define Aux BIT(5)
#define INH BIT(4)
#define A2 BIT(3)
#define SYS BIT(2)
#define IBF BIT(1)
#define OBF BIT(0)

//other usefull variables

#define ESC 0x81
#define IRQ_KB 1
#define TWO_BYTE 0xe0

#endif
