#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

#include "timer.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint32_t control_word = BIT(5) | BIT(4); // For LSB followed by MSB mode

  uint16_t initial_value = (uint16_t) TIMER_FREQ / freq;

  uint8_t timer_port, status, iv_lsb, iv_msb;

  switch(timer) {

    case 0: timer_port = 0x40;
            // bits estão os dois a 0 
            break;

    case 1: timer_port = 0x41;
            control_word |= BIT(6);
            break;

    case 2: timer_port = 0x42;
            control_word |= BIT(7);
            break;
    default: return 1;
  }

  if (timer_get_conf(timer_port, &status)) return 1;

  /** In order not to change the first **/

  uint8_t mask = 0x07;

  control_word |= (status & mask);

  if (sys_outb(timer_port, control_word)) return 1;


  /** Finally send the 16 bit word of frequency, needs to be handled first **/

  util_get_LSB(initial_value, &iv_lsb);
  util_get_MSB(initial_value, &iv_msb);

  /** Load timer’s register with the value of the divisor to
  generate the frequency corresponding to the desired
  rate
  **/

  if (sys_outb(initial_value, iv_lsb)) return 1;
  if (sys_outb(initial_value, iv_msb)) return 1;

  return 0;
}

/** value that is changed by irq_setpolicy and to be accessed by irq_rempolicy **/
static int hook_id;
int (timer_subscribe_int)(uint8_t *bit_no) {

  hook_id = TIMER0_IRQ;
  *bit_no = hook_id;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)) return 1;

  return 0;
}

int (timer_unsubscribe_int)() {

  if (sys_irqrmpolicy(&hook_id)) return 1;

  return 0;
}

int no_interrupts = 0;
void (timer_int_handler)() {
  no_interrupts++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if (timer < 0 || timer > 2 || st == NULL) return 1;

  /** See 2timer.pdf slide 9 for read_back command assembly **/

  // CHECK AFTER IF IT IS A 32 OR 8 BIT ONLY
  uint32_t RB_CMD = TIMER_RB_CMD | TIMER_RB_COUNT_;

  switch(timer) {

    case 0: RB_CMD |= BIT(1); break;

    case 1: RB_CMD |= BIT(2); break;

    case 2: RB_CMD |= BIT(3); break; 
  }

  /** Signal to register 0x43 (Control Register for Timers) that we wish to perfoma a read-back command **/
  if(sys_outb(0x43, RB_CMD)) return 1;

  /** Reads from a chosen timer to status **/
  if(util_sys_inb(TIMER_0 + timer, st)) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

    union timer_status_field_val conf;
    uint8_t tsf_initial_mode;

    /** Slide 15 and 16 for this part, but also slide 7 for the control word from 2timer.pdf **/
    switch(field) {
      
      case tsf_all: conf.byte = st; break;
      case tsf_initial: 
        tsf_initial_mode = (st & (BIT(5) | BIT(4)));

        switch (tsf_initial_mode) {
          case 1: conf.in_mode = TIMER_LSB; break; // BIT(4)
          case 2: conf.in_mode = TIMER_MSB; break; // BIT(5);
          case 3: conf.in_mode = TIMER_LSB_MSB; break; // BIT(4) | BIT(5)
          default: return 1;
        } 
        break;
      case tsf_mode:
        conf.count_mode = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
        if (conf.count_mode == 6) conf.count_mode = 2;
        if (conf.count_mode == 7) conf.count_mode = 3;
        break;
      case tsf_base:
        conf.bcd = (st & BIT(0));
        break;
    }

    return timer_print_config(timer, field, conf);
}
