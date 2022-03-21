#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int cntr = 0;
uint16_t cntr_reg;

#define TIMER_COUNTMODE 0x0E
#define TIMER_INMODE 0x30



int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint8_t status, lsb, msb, timer_port, cntrlW;

  uint16_t startValue = (uint16_t)(TIMER_FREQ/freq);

  switch (timer)
  {
    case 0:
      timer_port = TIMER_0;
      cntrlW = TIMER_SEL0;
      break;
    case 1:
      timer_port = TIMER_1;
      cntrlW = TIMER_SEL1;
      break;
    case 2:
      timer_port = TIMER_2;
      cntrlW = TIMER_SEL2;
      break;
    default:
      return 1;
  }

  if(timer_get_conf(timer, &status))
    return 1;
  uint8_t mk = 0x0F;
  cntrlW |= TIMER_LSB_MSB | (status & mk);

  if (sys_outb(TIMER_CTRL, cntrlW) != OK) {
      printf("%s: sys_outb() failed \n", __func__);
      return 1;
    }
  if(util_get_LSB(startValue, &lsb))
    return 1;

  if (sys_outb(startValue, lsb))
    return 1;

  if (util_get_MSB(startValue, &msb))
    return 1;

  if (sys_outb(startValue, msb))
    return 1;
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

  int rPort;
  uint32_t cmdW = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if (sys_outb(TIMER_CTRL, cmdW)) return 1;
  

  switch(timer) {
    case 0: rPort = TIMER_0;
      break;
    case 1: rPort = TIMER_1;
      break;
    case 2: rPort = TIMER_2;
      break;
    default:
      return 1;
  }

  if (util_sys_inb(rPort, st))
    return 1;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  
  uint8_t inMode;
  union timer_status_field_val config;
  
  switch (field) {

    
    case tsf_initial: 
        inMode = (st & TIMER_INMODE) >> 4;

        switch(inMode) {

          case 0: config.in_mode = INVAL_val; break;

          case 1: config.in_mode = LSB_only; break;

          case 2: config.in_mode = MSB_only; break;

          case 3: config.in_mode = MSB_after_LSB; break; 

          default:
            return 1;
        }
        break;

    case tsf_mode:
        config.count_mode = (st & TIMER_COUNTMODE) >> 1;
    case tsf_all:
      config.byte = st; break;
    case tsf_base:
        config.bcd = st & TIMER_BCD;
        break;
    default: return 1;

    if (timer_print_config(timer, field, config)) return 1;
    return 0;
    }
  return 1;
}
