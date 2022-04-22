#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include <i8042.h>
#include <kbd.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern uint8_t out_byte;
int(kbd_test_scan)() {
  uint8_t bit_no = KBD_IRQ;
  uint32_t r,irq_set = BIT(bit_no);
  int ipc_status;
  uint8_t bytes[2];
  message msg;

  if(kbd_subscribe_int(&bit_no)){
      printf("Error in kbd_test_scan(), kbd_subscribe_int()!")
      return 1;
  }
 
 while( bytes[0] != KBD_ESC_BREAKCODE ) { /* You may want to use a different condition */
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
           case HARDWARE: /* hardware interrupt notification */				
               if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    kbc_ih();
                    bytes[size] = out_byte;

                    if(out_byte == 0)
                        return 1;
                    
                    if(out_byte != 0xE0){
                      kbd_print_scancode(isMakeCode(out_byte),size+1,bytes);
                      size=0;
                    }
                    else size++;
               }
                break;
           default:
               break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
    kbd_unsubscribe_int();
    return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}