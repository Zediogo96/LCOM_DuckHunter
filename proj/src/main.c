// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "i8042.h"
#include "i8254.h"

#include "images/ducks.xpm"
#include "keyboard.h"
#include "timer.h"
#include "utils.h"
#include "vbe.h"
#include "video_gr.h"

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

extern uint8_t out_byte;

int(proj_main_loop)(int argc, char *argv[]) {

  uint8_t bit_no = KBD_IRQ;
  uint32_t kbd_irq = BIT(bit_no);

  /* uint8_t timer_irq = TIMER0_IRQ;
  uint32_t mouse_irq = MOUSE_IRQ; */

  int r, ipc_status, size = 0;
  message msg;

  uint8_t bytes[2];

  xpm_image_t img;
  xpm_load(ducks_xpm, XPM_8_8_8_8, &img);

  vg_init(0x14C);

  /* if (timer_subscribe_int(&timer_irq)) {
    printf("%s failed!", __func__);
    return 1;
  } */

  if (kbd_subscribe_int(&bit_no)) {
    printf("%s failed!", __func__);
  }

  while (bytes[0] != KBD_BREAKCODE_ESC) { /* You may want to use a different condition */

    vg_draw_image(img, 50, 50);    // vg_draw_image(img, 0,0);


    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             /* hardware interrupt notification */
          if (msg.m_notify.interrupts & kbd_irq) { /* subscribed interrupt */
            kbc_ih();
            bytes[size] = out_byte;

            if (out_byte == 0)
              return 1;

            if (out_byte != 0xE0) {
              size = 0;
            }
            else
              size++;
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

  // if (timer_unsubscribe_int()) {
  //   printf("%s failed!", __func__);
  //   return 1;
  // }

  if (kbd_unsubscribe_int()) {
    printf("%s failed!", __func__);
    return 1;
  }
  vg_exit();

  return 0;
}
