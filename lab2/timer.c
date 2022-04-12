#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include <minix/syslib.h>

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
