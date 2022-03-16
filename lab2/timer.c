#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

#include <minix/syslib.h>

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
    uint16_t initial_value = (uint16_t)(TIMER_FREQ / freq);
    uint8_t status, control_word, timer_port, init_val_lsb, init_val_msb;

    switch(timer) {
      case 0: 
          control_word = TIMER_SEL0;
          timer_port = TIMER_0;
          break;
      case 1:
          control_word = TIMER_SEL1;
          timer_port = TIMER_1;
          break;
      case 2:
          control_word = TIMER_SEL2;
          timer_port = TIMER_2;
          break;
      default:
          return 1;
    }
    
    // get status value 
    if (timer_get_conf(timer, &status)) return 1;

    uint8_t mask = 0x0F;
    control_word |= TIMER_LSB_MSB | (status & mask);

    if (sys_outb(TIMER_CTRL, control_word) != OK) {
      printf("%s: sys_outb() failed \n", __func__);
      return 1;
    }

    /** Splits 16 bit word (IV) into 2 bytes **/
    if(util_get_LSB(initial_value, &init_val_lsb)) return 1;
    if (util_get_MSB(initial_value, &init_val_msb)) return 1;

    if (sys_outb(initial_value, init_val_lsb)) return 1;
    if (sys_outb(initial_value, init_val_msb)) return 1;

  return 0;
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

  #define TIMER_INMODE_MASK 0x30 // 0x00110000 (bit pos 5 e 4)
  #define TIMER_COUNTMODE_MASK 0x0E // 0x00001110 (bit pos 3, 2 e 1)

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
