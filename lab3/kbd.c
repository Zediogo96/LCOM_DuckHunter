#include <lcom/lcf.h>
#include <kbd.h>
#include <i8042.h>

    static int hook_id;

int kbd_subscribe_int(uint8_t *bit_no){
    hook_id= KBD_IRQ;
    * bit_no = (uint8_t) (hook_id);

    if((sys_irqsetpolicy(KBD_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)) != OK){
        printf("Error in kbd_subscribe_int, sys_irqsetpolicy()!");
        return 1;
    }
    return 0;
}

int kbd_unsubscribe_int(){
    if((sys_irqrmpolicy(&hook_id)) != OK){
        printf("Error in kbd_unsubscribe_int, sys_irqrmpolicy()!");
        return 1;
    }
    return 0;
}

void (kbc_ih)(){
    while(1) {
        if(kbc_read_outb() == 0){
            break;
        }
    }
}

uint8_t out_byte;
int (kbc_read_outb)(){
    out_byte = 0;
    uint8_t stat;
    if(util_sysinb(KBD_STATUS_REG, &stat)!=OK){
        printf("%s: util_sys_inb() failed\n", __func__);
    return 1;
    }
    if(stat & KBD_OUTPUT_BUFFER_FULL){
        uint8_t data;
        if(util_sys_inb(KBD_OUTPUT_BUF, &data) != OK){
      printf("%s: util_sys_inb() failed\n", __func__);
      return 1;
    }
    if((stat &(KBD_PARITY_ERROR| KBD_TIMEOUT_ERROR))==0){
        out_byte = data;
        return 0;
    }
    else{
         printf("%s: KBC_PAR_ERR or KBC_TO_ERR occured\n", __func__);
      return 1;

    }
    }
    return 1;
}