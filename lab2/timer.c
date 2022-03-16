#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

#include <minix/syslib.h>

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

  /** Note that the second argument of sys_inb() 
   * must be the address of a 32-bit unsigned integer variable **/

  // TIMER_RB_CMD => sets bit 7 and 6 to 1;
  // TIMER_RB_COUNT_ => set bit 5 to 1;
  // TIMER_RB_SEL(timer) => enables bit corresponding to the desired timer

  u32_t cmd_word = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  if (sys_outb(TIMER_CTRL, cmd_word)) return 1;

  int read_port;

  switch(timer) {
    case 0: read_port = TIMER_0; break;
    case 1: read_port = TIMER_1; break;
    case 2: read_port = TIMER_2; break;
    default: return 1;
  }

  // READ WAS SUCCESSFUL 
  if (util_sys_inb(read_port, st)) return 1;
  // WAS NOT
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

  union timer_status_field_val conf;
  

  return 1;
}
