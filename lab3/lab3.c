#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"

#include "timer/timer.c"

#include "utils.h"

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
  uint32_t irq_set = BIT(bit_no);
  int r, ipc_status, size = 0;
  uint8_t bytes[2];
  message msg;

  if (kbd_subscribe_int(&bit_no) != 0) return 1;

  while (bytes[0] != KBD_BREAKCODE_ESQ) { // CHANGE

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
    }

    if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                          kbc_ih();
                          bytes[size] = out_byte;
  
                          if (out_byte == 0) return 1;

                          // meaning it only has one byte
                          // ou têm dois byts
                          if (out_byte != 0xE0) {
                          kbd_print_scancode(isMakeCode(out_byte), size + 1, bytes);
                          size = 0;
                          }
                          else size++;
                    }
                    break;
                    default:
                    break; /* no other notifications expected: do nothing */
            }
    } else { 
      /* received standart message, not a notification */
      /* no standart message expected: do not */
      }          
    }

    kbd_unsubscribe_int(bit_no);
  return 0;
}
  

int(kbd_test_poll)() {
  

  uint8_t bytes[2]; // can be 1 or 2 bytes long

  int size = 0;

  while (out_byte != KBD_BREAKCODE_ESQ) {

    kbc_poll();

    if (out_byte) { // meaning it's different than 0
        bytes[size] = out_byte;

        if (out_byte != 0xE0) {
            kbd_print_scancode(isMakeCode(out_byte), size + 1, bytes);
            size = 0;
        }
        else size++;
    }
  }

  /** READ CURRENT COMMAND BYTE TO OUTBYTE **/
  kbc_issue_command(KBD_READ_CMD, KBD_CMD_REG);
  kbc_read_outb();

  /** WRITE COMMAND BYTE WITH INTERRUPT ENABLED **/
  kbc_issue_command(KBD_WRITE_CMD, KBD_CMD_REG);
  kbc_issue_command(out_byte | BIT  (0), KBD_WRITE_CMD);
  
  return 0;
}


int(kbd_test_timed_scan)(uint8_t n) {

  uint8_t bytes[2]; 
  int ipc_status, r;
  message msg;

  // TIMER INTERRUPT HANDLING
  const uint32_t FREQ = 60;
  uint8_t timer_id = TIMER0_IRQ;
  uint8_t timer_irq_set  = BIT(timer_id);

  int no_interrupts = 0;

  if (timer_subscribe_int(&timer_id) != 0) {
      perror("Error ocurred while subscribing timer_bit");
  }

  int size = 0;

  // KEYBOARD INTERRUPT HANDLING
  uint8_t kbd_id = KBD_IRQ;
  uint8_t kbd_irq_set = BIT(kbd_id);

  if (kbd_subscribe_int(&kbd_id) != 0) {
      perror("Error ocurred while subscribing kbd_bit");
  }


  // MAIN LOOP AFTER SUBSCRIBING BOTH I/O DEVICES
  while (bytes[0] != KBD_BREAKCODE_ESQ && timer_counter < n) { // CHANGE

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
    }

    if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */

                    if (msg.m_notify.interrupts & timer_irq_set) {
                      timer_int_handler();
                      if (no_interrupts % FREQ == 0) global_int_counter++;
                    }
                    
                    if (msg.m_notify.interrupts & kbd_irq_set) { /* subscribed interrupt */
                          kbc_ih();
                          bytes[size] = out_byte;
  
                          if (out_byte == 0) return 1;

                          // meaning it only has one byte
                          if (out_byte != 0xE0) {
                          kbd_print_scancode(isMakeCode(out_byte), size + 1, bytes);
                          size = 0;
                          }
                          else size++;
                    }
                    break;
                    default:
                    break; /* no other notifications expected: do nothing */
            }
    } else { 
      /* received standart message, not a notification */
      /* no standart message expected: do not */
      }          
    }

    kbd_unsubscribe_int();
    timer_unsubscribe_int();

  return 0;
}

