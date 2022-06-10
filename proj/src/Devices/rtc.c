#include "Include/rtc.h"
#include "Include/utils.h"
#include <lcom/lcf.h>

bool isBCD() {

  uint32_t value;

  sys_outb(RTC_REG_ADDRESS, RTC_REG_B);
  sys_inb(RTC_REG_DATA, &value);

  if (value & DM_FLAG)
    return false;
  else
    return true;
}

uint32_t BCD_2_Binary(uint32_t bcd) {
  uint32_t binary = 0;
  binary = (((bcd) &0xF0) >> 4) * 10 + ((bcd) &0x0F);
  return binary;
}

void getCurrentTime(uint8_t *hours, uint8_t *minutes) {

  uint32_t h = 0, m = 0, temp_hours = 0;

  sys_outb(RTC_REG_ADDRESS, RTC_HOUR);
  sys_inb(RTC_REG_DATA, &h);
  sys_outb(RTC_REG_ADDRESS, RTC_MIN);
  sys_inb(RTC_REG_DATA, &m);

  if (isBCD()) {

    temp_hours = BCD_2_Binary(h);

    (((h & 0xF0) >> 4) == 0x08) ? (*hours = ((h - 0x80 + 13))) : (*hours = BCD_2_Binary(h));
    (*minutes) = BCD_2_Binary(m) - 10;
  }
}
