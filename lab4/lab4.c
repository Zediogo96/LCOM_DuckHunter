// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "timer.c"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern int hookID;
extern uint8_t out_byte;

int(mouse_test_packet)(uint32_t cnt) {

  struct device_info mouse = create_device(MOUSE_IRQ);

  mouse_enable_data_reporting();

  if (mouse_subscribe_int(&mouse.bit_no)) {
    printf("%s: mouse_subscribe_int() failed\n", __func__);
    return 1;
  }

  mouse.hookID = hookID;

  int r, ipc_status;
  message msg;

  // SIMILAR TO KEYBOARD, BUT HAS ONE ADDITIONAL BYTE
  uint8_t bytes[3];
  uint8_t byte_count = 0;
  uint32_t packets_received = 0;

  while (packets_received < cnt) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & mouse.irq_set) {
            mouse_ih();
            if (out_byte & BIT(3) || byte_count != 0) {
              bytes[byte_count] = out_byte;
              byte_count++;
            }
            if (byte_count == 3) {
              byte_count = 0;
              packets_received++;

              struct packet pp = process_packets(bytes);

              mouse_print_packet(&pp);
            }
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

  hookID = mouse.hookID;
  if (mouse_unsubscribe_int() != 0) {
    printf("%s: mouse_unsubscribe_int() failed\n", __func__);
  }
  if (mouse_disable_reporting() != 0) {
    printf("%s: mouse_disable_reporting() failed\n", __func__);
  }
  return 0;
}

uint64_t no_interrupts;
int(mouse_test_async)(uint8_t idle_time) {

  struct device_info timer = create_device(TIMER0_IRQ);
  struct device_info mouse = create_device(MOUSE_IRQ);

  /** Still using LCF version */
  mouse_enable_data_reporting();

  /** Interrupt Subscribes **/
  if (timer_subscribe_int(&timer.bit_no))
    return 1;
  timer.hookID = hookID;
  if (mouse_subscribe_int(&mouse.bit_no))
    return 1;
  mouse.hookID = hookID;

  int r, ipc_status;
  message msg;

  const uint8_t FREQ = sys_hz();

  uint8_t bytes[3];
  uint8_t byte_count = 0;
  uint8_t timer_left = idle_time;
  no_interrupts = 0;

  while (timer_left != 0) { /* You may want to use a different condition */
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & timer.irq_set) {
            timer_int_handler();
            if (no_interrupts % FREQ == 0) {
              timer_left--;
            }
          }
          if (msg.m_notify.interrupts & mouse.irq_set) {
            timer_left = idle_time;
            no_interrupts = 0;
            mouse_ih();
            if (out_byte & BIT(3) || byte_count != 0) {
              bytes[byte_count] = out_byte;
              byte_count++;
            }
            if (byte_count == 3) {
              byte_count = 0;

              struct packet pp = process_packets(bytes);

              mouse_print_packet(&pp);
            }
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

  hookID = mouse.hookID;
  if (mouse_unsubscribe_int() != 0) {
    printf("%s: mouse_unsubscribe_int() failed\n", __func__);
  }
  hookID = timer.hookID;
  if (timer_unsubscribe_int() != 0) {
    printf("%s: timer_unsubscribe_int() failed\n", __func__);
  }
  if (mouse_disable_reporting() != 0) {
    printf("%s: mouse_disable_reporting() failed\n", __func__);
  }
  return 0;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt) {
  /* To be completed */
  printf("%s(%u, %u): under construction\n", __func__, period, cnt);
  return 1;
}
