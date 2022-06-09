#ifndef _RTC_H_
#define _RTC_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define RTC_HOUR 0x04
#define RTC_MIN 0x02
#define RTC_SEC 0x00

#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_C 0x0C
#define RTC_REG_D 0x0D

#define UIP_FLAG BIT(7)
#define DM_FLAG BIT(2)

#define RTC_REG_ADDRESS 0x70
#define RTC_REG_DATA 0x71

bool isBCD();

uint32_t BCD_2_Binary(uint32_t bcd);

void getCurrentTime(uint32_t* hours, uint32_t* minutes);

#endif
