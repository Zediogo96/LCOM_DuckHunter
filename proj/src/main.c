// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "i8042.h"
#include "i8254.h"

#include "keyboard.h"
#include "timer.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(main_loop)(int argc, char *argv[]) {

  uint8_t kbd_irq = KBD_IRQ;
  uint8_t timer_irq = TIMER0_IRQ;
  uint32_t mouse_irq = MOUSE_IRQ;

  int r, ipc_status;
  message msg;

  /* if (vg_init()) {
    printf("%s failed!", __func__);
    return 1;
  }
 */
  if (timer_subscribe_int(&timer_irq)) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (kbd_subscribe_int(&kbd_irq)) {
    printf("%s failed!", __func__);
  }

  while (1) { // must be game != end
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                                   /* hardware interrupt notification */
          if (msg.m_notify.interrupts & timer_irq) { /* subscribed interrupt */
          }
          if (msg.m_notify.interrupts & kbd_irq) { /* subscribed interrupt */
            kbc_ih();
          }
          if (msg.m_notify.interrupts & mouse_irq) {
            mouse_ih();
          }

          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
    else { /* received a standard message, not a notification */
           /* no standard messages expected: do nothing */
    }
  }

  /**
   * STUFF TO DISABLE MOUSE AND MOUSE DATA REPORTING
   **/

  if (timer_unsubscribe_int()) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (kbd_unsubscribe_int()) {
    printf("%s failed!", __func__);
    return 1;
  }
  if (vg_exit()) {
    printf("%s failed!", __func__);
    return 1;
  }
  

  return 0;
}
