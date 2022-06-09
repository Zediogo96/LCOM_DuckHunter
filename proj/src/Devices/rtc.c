#include "../Include/rtc.h"
#include "util.h"
#include <lcom/lcf.h>

int hook_id;
int rtc_subscribe_int(uint8_t *bit_no) {
  hook_id = RTC_IRQ;
  *bit_no = (uint8_t) hook_id;
  if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_id) != OK) {
    printf("%s: sys_irqsetpolicy() failed\n", __func__);
    return 1;
  }
  return 0;
}

int rtc_unsubscribe_int() {
  if (sys_irqrmpolicy(&hook_id) != OK) {
    printf("%s: sys_irqrmpolicy() failed\n", __func__);
    return 1;
  }
  return 0;
}


int(rtc_read_register)(uint32_t reg, uint8_t *data) {
  if (sys_outb(RTC_REG_ADDRESS, reg))
    return 1;

  if (util_sys_inb(RTC_REG_DATA, data))
    return 1;

  return 0;
}

int(rtc_write_register)(uint32_t reg, uint8_t data) {
  if (sys_outb(RTC_REG_ADDRESS, reg))
    return 1;

  if (sys_outb(RTC_REG_DATA, data))
    return 1;

  return 0;
}

void rtc_init() {

  uint8_t status;
  rtc_read_register(RTC_REG_B, &status);
  status |= BIT(1);
  status &= ~BIT(2);
  rtc_write_register(RTC_REG_B, status);
}

void convertTimePortugal(uint32_t *hours, uint32_t *minutes) {
  *hours = (*hours + 11) % 24;
  *hours = (*minutes - 30) % 60;
}

uint32_t BCD_2_Binary(uint32_t bcd) {
  uint32_t binary;

  binary = (((bcd) & 0xF0) >> 4) * 10 + ((bcd) & 0x0F);

  return binary;
}

void getCurrentTime(uint32_t *hours, uint32_t *minutes) {

  uint32_t h = 0, m = 0;


  sys_outb(RTC_REG_ADDRESS, RTC_HOUR);
  sys_inb(RTC_REG_DATA, &h);
  sys_outb(RTC_REG_ADDRESS, RTC_MIN);
  sys_inb(RTC_REG_DATA, &m);

  (*hours) = BCD_2_Binary(h);
  (*minutes) = BCD_2_Binary(m);

  /*  convertTimePortugal(hours, minutes); */
}
