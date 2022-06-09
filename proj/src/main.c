// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "Include/i8042.h"
#include "Include/i8254.h"

#include "Include/crosshair.h"
#include "Include/database.h"
#include "Include/duck.h"
#include "Include/hitboxes.h"
#include "Include/keyboard.h"
#include "Include/mouse.h"
#include "Include/rtc.h"
#include "Include/timer.h"
#include "Include/utils.h"
#include "Include/vbe.h"
#include "Include/video_gr.h"

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

uint64_t no_interrupts = 0; // prob change inside the loop
uint32_t hours = 0, minutes = 0;

int(proj_main_loop)(int argc, char *argv[]) {

  uint8_t bit_no_kbd = KBD_IRQ;
  uint8_t bit_no_timer = TIMER0_IRQ;
  uint8_t bit_no_mouse = MOUSE_IRQ;
  uint8_t bit_no_rtc = RTC_IRQ;
  uint32_t kbd_irq = BIT(bit_no_kbd);
  uint32_t timer_irq = BIT(bit_no_timer);
  uint32_t mouse_irq = BIT(bit_no_mouse);
  uint32_t rtc_irq = BIT(bit_no_rtc);

  int r, ipc_status, size = 0;
  message msg;

  uint8_t bytes[2];

  // For Mouse Handling
  uint8_t mouse_byte_count = 0;
  struct packet pp;
  uint8_t bytes_mouse[3];
  mouse_enable_data_reporting(); // Still using LCF version

  vg_init(MODE_1152x864_DIRECT);

  loadAllXPMs();

  Database *db = getDB();

  gameInit();

  rtc_init();

  /* get_hour(&min, &hours); */

  if (timer_subscribe_int(&bit_no_timer)) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (kbd_subscribe_int(&bit_no_kbd)) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (mouse_subscribe_int(&bit_no_mouse)) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (rtc_subscribe_int(&bit_no_rtc))
    return 1;

  while (db->currentState != Exit) { /* You may want to use a different condition */
    getCurrentTime(&hours, &minutes);
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & rtc_irq) {
          }
          if (msg.m_notify.interrupts & timer_irq) {

            if (db->currentState == GamePlaying) {

              if (db->lives == 0) {

                db->currentState = GameOver;
              }

              timer_int_handler();

              if (no_interrupts % 200 == 0) {
                create_Duck(db);
                create_Duck(db);
              }

              drawBackground(hours, minutes);
              drawCrosshair();
              draw_fullScore();
              draw_fullLives();

              if (no_interrupts % 30 == 0) {
                update_ducks_dir();
              }

              update_ducks_status();
              draw_ducks();

              checkDuckGotShot(db->sprites->crosshair);

              if (db->ghostScore == 100) {
                db->gameSpeed++;
                db->ghostScore = 0;
              }
            }

            else if (db->currentState == Menu) {
              drawMainMenu();
            }
            else if (db->currentState == Menu_Rules) {
              vg_draw_rectangle(300, 450, 550, 350, 0x000000);
              vg_draw_image(db->images.rules_text, 270, 500);
            }

            else if (db->currentState == GamePaused) {
              drawPausedIndicator();
            }
            else if (db->currentState == GameOver) {
              vg_draw_image(db->images.gameOver, 440, 310);
              vg_draw_image(db->images.gameOver_text, 250, 500);
            }

            copyDoubleBufferToMain();
          }
          if (msg.m_notify.interrupts & mouse_irq) {
            mouse_ih();

            bytes_mouse[mouse_byte_count] = out_byte;
            mouse_byte_count++;

            if (mouse_byte_count == 3) {
              mouse_byte_count = 0;

              pp = process_packets(bytes_mouse);
              update_mouse(pp, db);
            }
          }
          if (msg.m_notify.interrupts & kbd_irq) { /* subscribed interrupt */
            kbc_ih();
            bytes[size] = out_byte;

            if (out_byte == 0)
              return 1;

            if (out_byte != 0xE0) {
              if (db->currentState == Menu)
                updateCurrentSelect(out_byte);
              else if (db->currentState == GamePlaying || db->currentState == GamePaused) {
                handlePause(out_byte);
                if (out_byte == KBD_BREAKCODE_ESC) {
                  gameReset();
                  db->currentState = Menu;
                }
              }
              else if (db->currentState == GameOver) {
                if (out_byte == KBD_BREAKCODE_ESC) {
                  gameReset();
                  db->currentState = Menu;
                }
                if (out_byte == KBD_BREAKCODE_R) {
                  gameReset();
                  db->currentState = GamePlaying;
                }
              }
              else if (db->currentState == Menu_Rules) {
                if (out_byte == KBD_BREAKCODE_ESC) {
                  db->currentState = Menu;
                }
              }

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
  if (timer_unsubscribe_int()) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (kbd_unsubscribe_int()) {
    printf("%s failed!", __func__);
    return 1;
  }

  if (mouse_disable_reporting() != 0) {
    printf("%s: mouse_disable_reporting() failed\n", __func__);
  }

  if (mouse_unsubscribe_int()) {
    printf("%s failed!", __func__);
    return 1;
  }

  gameDestroy();

  vg_exit();

  return 0;
}
