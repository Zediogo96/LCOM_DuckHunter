#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <keyboard.h>
#include <i8042.h>

static int hook_id;

int kbc_issue_command(uint8_t cmd, int port) {

  uint8_t status = 0;
  int count_cycles = 0;

  while (count_cycles++ < 20) {
    if (util_sys_inb(KBD_STATUS_REG, &status) != 0) return 1; 

    if ((status & KBD_INPUT_BUFFER_FULL) == 0) { //IS NOT FULL
        sys_outb(port, cmd);
        printf("%s: Wrote 0x%x to port 0x%x", __func__, cmd, KBD_STATUS_REG);
        return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }

  printf("Exiting %s with insuccess", __func__);

  return 1;

}

uint8_t out_byte;
int kbc_read_outb(){
  out_byte = 0;
  uint8_t stat;
  if(util_sys_inb(KBD_STATUS_REG, &stat) != OK){
    printf("%s: util_sys_inb() failed\n", __func__);
    return 1;
  } 
  if( stat & KBD_OUTPUT_BUFFER_FULL ) {
    uint8_t data;
    if(util_sys_inb(KBD_OUTPUT_BUF, &data) != OK){
      printf("%s: util_sys_inb() failed\n", __func__);
      return 1;
    }
    if ( (stat &(KBD_PARITY_ERROR| KBD_TIMEOUT_ERROR)) == 0 ){
      out_byte = data;
      return 0;
    }
    else {
      printf("%s: KBC_PAR_ERR or KBC_TO_ERR occured\n", __func__);
      return 1;
    }
  }
  return 1;
}

void(kbc_ih)(){
  while( 1 ) {
    if(kbc_read_outb() == 0){
      break;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

void kbc_poll(){
  kbc_read_outb();
  tickdelay(micros_to_ticks(DELAY_US));
}


int kbd_subscribe_int(uint8_t *bit_no) {
  hook_id = KBD_IRQ;
  *bit_no = (uint8_t) hook_id;
  if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK){
    printf("%s: sys_irqsetpolicy() failed\n", __func__);
    return 1;
  }
  return 0;
}

int kbd_unsubscribe_int() {
  if(sys_irqrmpolicy(&hook_id) != OK){
      printf("%s: sys_irqrmpolicy() failed\n", __func__);
      return 1;
  }
  return 0;
}

