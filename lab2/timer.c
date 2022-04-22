#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include <minix/syslib.h>

#include "i8254.h"

extern uint64_t counter; // usada no timer_handler();

int timer_hook_id; // IRQ OF Timer0 (timer)

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
    uint8_t controlWord, lsb, msb;
    uint32_t newControlWord;

    //reads the control word(status)
    if(timer_get_conf(timer, &controlWord)){
      printf("ERROR: Invalid timer value\n");
      return 1;
    }

    uint8_t control_lsb = (BIT(0) | BIT(1) | BIT(2) | BIT(3)) & controlWord; // saves 4 lsb on control lsb

    uint16_t divisor = (uint16_t)(TIMER_FREQ / freq);

    if(util_get_LSB(divisor,&lsb)){
      printf("Error in timer_set_frequency, util_get_lsb");
      return 1;
    }

    if(util_get_MSB(divisor,&msb) != 0){
      printf("Error in timer_set_frequency, util_get_msb");
      return 1;
    }

    switch(timer){
      case 0:
          newControlWord = control_lsb | TIMER_SEL0 | TIMER_LSB_MSB; // control_lsb -> bits de 0 a 3; Timer_sel0 -> bits 7,6; timer_lsb_msb-> bits 5,4 
          if(sys_outb(TIMER_CTRL, newControlWord) != 0){
            printf("Error in timer_set_frequency, timer_0 ctrl sys_outb\n");
            return 1;
          } // escreve a newcontrolword no timer_ctrl
          if(sys_outb(TIMER_0, lsb)!=0){
            printf("Error in timer_set_frequency, timer_0 lsb sys_outb\n");
            return 1;
          }; //escreve lsb de frequencia divisor no timer_0
          if(sys_outb(TIMER_0, msb) != 0){ 
            printf("Error in timer_set_frequency, timer_0 msb sys_outb\n");
            return 1;
          } //escreve lsb de frequencia divisor no timer_0
          break;
        case 1:
          newControlWord = control_lsb | TIMER_SEL1 | TIMER_LSB_MSB; // control_lsb -> bits de 0 a 3; Timer_sel0 -> bits 7,6; timer_lsb_msb-> bits 5,4 
          if(sys_outb(TIMER_CTRL, newControlWord) != 0){
            printf("Error in timer_set_frequency, timer_1 trl sys_outb\n");
            return 1;
          } // escreve a newcontrolword no timer_ctrl
          if(sys_outb(TIMER_1, lsb)!=0){
            printf("Error in timer_set_frequency, timer_1 lsb sys_outb\n");
            return 1;
          }; //escreve lsb de frequencia divisor no timer_0
          if(sys_outb(TIMER_1, msb) != 0){ 
            printf("Error in timer_set_frequency, timer_1 msb sys_outb\n");
            return 1;
          } //escreve lsb de frequencia divisor no timer_0
        break;
        case 2:
          newControlWord = control_lsb | TIMER_SEL2| TIMER_LSB_MSB; // control_lsb -> bits de 0 a 3; Timer_sel0 -> bits 7,6; timer_lsb_msb-> bits 5,4 
          if(sys_outb(TIMER_CTRL, newControlWord) != 0){
            printf("Error in timer_set_frequency, timer_2 ctrl sys_outb\n");
            return 1;
          } // escreve a newcontrolword no timer_ctrl
          if(sys_outb(TIMER_2, lsb)!=0){
            printf("Error in timer_set_frequency, timer_2 lsb sys_outb\n");
            return 1;
          }; //escreve lsb de frequencia divisor no timer_0
          if(sys_outb(TIMER_2, msb) != 0){ 
            printf("Error in timer_set_frequency, timer_2 msb sys_outb\n");
            return 1;
          } //escreve lsb de frequencia divisor no timer_0
          break;


    }
    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  timer_hook_id = TIMER0_IRQ; 
  *bit_no = (uint8_t) timer_hook_id;

  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id)){
      printf("sys_irqsetpolicy() failed\n");
      return 1;
  }
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timer_hook_id)){
      printf("sys_irqrmpolicy() failed\n");
      return 1;
  }
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
    uint8_t readback = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

    if(sys_outb(TIMER_CTRL,readback) != OK){
        printf("ERRORsys_outb falhou\n");
        return 1;
    }
    switch (timer) {
        case 0:
            if(util_sys_inb(TIMER_0, st)) 
            return 1;
            break;
        case 1:
            if(util_sys_inb(TIMER_1,st)) 
            return 1;
            break;
        case 2:
            if(util_sys_inb(TIMER_2, st)) 
            return 1;
            break;
        default:
          return 1;
    }
    return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
    union timer_status_field_val conf;
    uint8_t in_mode;

    #define TIMER_INMODE_MASK 0x30
    #define TIMER_COUNTMODE_MASK 0x0E 

    // tsf_ all ->  all the configuration status
    // tsf_initial -> timer inatialization mode
    // tsf_mode -> timer counting mode
    // tsf_base -> timer counting base 
    switch (field)
    {
        case tsf_all: 
            conf.byte=st;
            break;

        case tsf_initial:
            in_mode = (st & TIMER_INMODE_MASK) >> 4; // TIMER_INMODE_MASK 0x00110000
            switch (in_mode)
            {
                case 0: conf.in_mode = INVAL_val;
                        break;
                case 1: conf.in_mode = LSB_only;
                        break;
                case 2: conf.in_mode = MSB_only;
                        break;
                case 3: conf.in_mode = MSB_after_LSB;
                        break;
            default:
              return 1;
            }
            break;
        
        case tsf_mode:
            conf.count_mode = (st & TIMER_COUNTMODE_MASK)>>1;

            if (conf.count_mode == 6) conf.count_mode = 2;
            if (conf.count_mode == 7) conf.count_mode = 3;
            break;

        case tsf_base:
            if (TIMER_BCD & st)
                conf.bcd = true;
            else 
                conf.bcd = false;
            break;
        default:
          return 1;
        }
    timer_print_config(timer, field, conf);
    return 0;
}
