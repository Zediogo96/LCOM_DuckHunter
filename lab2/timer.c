#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  if(timer >= 3 || timer < 0)
  {
      printf("Timer number invalid.");
      return 1;
  }
  uint8_t read_back = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL,read_back);

    switch (timer) {
        case 0:
             return util_sys_inb(TIMER_0,st);
        case 1:
             return util_sys_inb(TIMER_1,st);
        case 2:
             return util_sys_inb(TIMER_2,st);

    }
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  /* To be implemented by the students */

  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
