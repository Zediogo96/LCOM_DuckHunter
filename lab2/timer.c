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

  #define TIMER_INMODE_MASK 0x30 // 0x00110000 (bit pos 4 e 5)
  #define TIMER_COUNTMODE_MASK 0x0E // 0x00001110 (bit pos 1, 2 e 3)

  // @brief Union for storing values of timer status fields, including the full status byte
  union timer_status_field_val conf;
  uint8_t in_mode;
  
  // tsf_all,     /*!< configuration/status */ tsf_initial, /*!< timer initialization mode */ 
  // tsf_mode,    /*!< timer counting mode */  tsf_base     /*!< timer counting base */
  switch (field) {

    case tsf_all: conf.byte = st; break;
    case tsf_initial: 
        in_mode = (st & TIMER_INMODE_MASK) >> 4; // RIGHT SHIFT 

        switch(in_mode) {

          case 0: conf.in_mode = INVAL_val; break; // 0x000
          case 1: conf.in_mode = LSB_only; break; // 0x001
          case 2: conf.in_mode = MSB_only; break; // 0x010
          case 3: conf.in_mode = MSB_after_LSB; break; // 0x011
          default: return 1;
        }
        break;

    case tsf_mode:
        conf.count_mode = (st & TIMER_COUNTMODE_MASK) >> 1;

    case tsf_base:
        conf.bcd = st & TIMER_BCD;
        break;
    default: return 1;

    if (timer_print_config(timer, field, conf)) return 1;
    return 0;
    }
  return 1;
}
