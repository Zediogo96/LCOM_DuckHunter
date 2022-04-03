#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "var.h"
#include <kbc.h>

extern uint8_t scancode[3];
extern bool two_byte_scan_code;
extern int cnt;
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

int(kbd_test_scan)() {
  /* To be completed by the students */
  
  uint8_t bit_no;
  int ipc_status = 0;
  int r;
  message msg;
  

  if(subscribe_kbc(&bit_no))
  {
    printf("Could not subcribe to KBC");
    return 1;
  }
  uint8_t irq_set = BIT(bit_no);
  while(scancode[0] != ESC) { /* You may want to use a different condition *///help
     /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
   if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                      /* process it */
                    kbc_ih();
                    
                    uint8_t data[2];
                    data[0] = scancode[0];
                    data[1] = scancode[1];
                    if(scancode[2] == 1)//two byte scan code
                    {
                        kbd_print_scancode(!(scancode[1] & BIT(7)),2,data);
                    }
                    else if(scancode[2] == 2)// one byte scan code
                    {
                        kbd_print_scancode(!(scancode[0] & BIT(7)),1,data);
                    }
                    else if(scancode[2] == 0)
                    {
                      continue;//scan code not ready to be displayed
                    }
                    
                    
               }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
   } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
  
  if(unsubscribe_kbc())
  {
      printf("Could not unsubscribe KBC");
      return 1;
  }
  #ifdef LAB3
   kbd_print_no_sysinb(cnt);
  #endif

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
