#include <lcom/lcf.h>
#include "rtc.h"
#include "util.h"

int isBCD() {

  uint8_t value;

  sys_outb(RTC_REG_ADDRESS, RTC_REG_B);
  util_sys_inb(RTC_REG_DATA, &value);

  if (!(value & DM_FLAG))
    return 1;
  return 0;
}

uint32_t BCD_2_Binary(uint32_t bcd) {
  uint32_t binary;

  binary = ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F);

  return binary;
}

void getCurrentTime(uint32_t *hours, uint32_t *minutes) {

  uint32_t h = 0, m = 0;

  sys_outb(RTC_REG_ADDRESS, RTC_HOUR);
  sys_inb(RTC_REG_DATA, &h);
  sys_outb(RTC_REG_ADDRESS, RTC_MIN);
  sys_inb(RTC_REG_DATA, &m);

  if (isBCD()) {

    (*hours) = BCD_2_Binary(h);
    (*minutes) = BCD_2_Binary(m);
  }
}
