#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

uint32_t counter = 0;
int hookid = TIMER0_IRQ;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  if(timer >2 || timer < 0)
  {
    return 1;
  }
  //nova frequencia
  uint16_t newfrequency = TIMER_FREQ / freq;
  uint8_t msb=0,lsb=0;
  util_get_LSB(newfrequency,&lsb);
  util_get_MSB(newfrequency,&msb);
  //setup do comando a enviar
   uint8_t command =  TIMER_LSB_MSB | TIMER_SQR_WAVE | TIMER_BCD;
  //escolher o timer
  switch (timer)
  {
  case 0:
    command = command | TIMER_SEL0;
    sys_outb(TIMER_CTRL,command);
    sys_outb(TIMER_0,lsb);
    sys_outb(TIMER_0,msb);
    break;
  case 1:
    command = command | TIMER_SEL1;
    sys_outb(TIMER_CTRL,command);
    sys_outb(TIMER_1,lsb);
    sys_outb(TIMER_1,msb);
  case 2:
    command = command | TIMER_SEL2;
    sys_outb(TIMER_CTRL,command);
    sys_outb(TIMER_2,lsb);
    sys_outb(TIMER_2,msb);  
    break;
  default:
    return 1;
    break;
  }


  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    hookid = TIMER0_IRQ;
    *bit_no = hookid;
    sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE, &hookid);//help
  return 0;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */

  sys_irqrmpolicy(&hookid);//help

  return 0;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
    counter += 1;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  if(timer >= 3 || timer < 0)
  {
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
        default:
          return 1;     

    }
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  /* To be implemented by the students */
  union timer_status_field_val conf;
    switch (field) {
        case tsf_all:
            conf.byte = st;
            break;
        case tsf_initial:
                switch ((st & (BIT(5) | BIT(4))))
                {
                case TIMER_LSB:
                  conf.in_mode = LSB_only;
                  break;
                case TIMER_MSB:
                  conf.in_mode = MSB_only;
                  break;  
                case TIMER_LSB_MSB:
                  conf.in_mode = MSB_after_LSB;
                  break;
                default:
                  conf.in_mode = INVAL_val;
                  break;
                }
                break;
        case tsf_mode:
          conf.count_mode = (st &((BIT(1) | BIT(2) | BIT(3))))>>1;
          if(conf.count_mode ==(0x7))
          {
            conf.count_mode = 0x3;
          }
          if(conf.count_mode == 0x6)
          {
            conf.count_mode = 0x2;
          }
          break;
        case tsf_base:
          conf.bcd = st & TIMER_BCD;
          break;

    }
    return timer_print_config(timer,field,conf);
}
