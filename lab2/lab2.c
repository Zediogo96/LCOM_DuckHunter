#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

uint64_t timer_counter = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {

  uint8_t status;

  /** NEEDS TO BE PASSED status as a &, as it will be changed **/
  if (timer_get_conf(timer, &status)) return 1;

  if (timer_display_conf(timer, status, field)) return 1;

  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  
  if (timer_set_frequency(timer, freq)) return 1;

  return 0;
}

int(timer_test_int)(uint8_t time) {

  uint8_t bit_no = 0;
  timer_subscribe_int(&bit_no);
  printf("%s was sucessful.", __func__);
  uint32_t irq_set = BIT(bit_no);

  timer_counter = 0;

  uint8_t FREQ = 60;

  int ipc_status;
  message msg;

  while(time > 0 ) { /* You may want to use a different condition */

    /* Get a request message. */
    
    /* It should be used by device drivers to receive messages, including notifications, from the kernel or from other processes. The first argument specifies the sender of the messages we want to receive. The value ANY means that the driver accepts messages from any process. The second and third arguments are the addresses of variables of type message and int, which will be initialized, by the driver_receive() code, with the message received and IPC related status, respectively.*/
    int r;

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }

    /** MUST USE BIT() because we do not want the value of the bit_no, we want it's bit number **/
    
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  timer_int_handler();
                  if (timer_counter % FREQ == 0) {
                    timer_print_elapsed_time();
                  }                    /* process it */
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
  }
  /** Must unsubscribe the current bit_no as it ends **/
  timer_unsubscribe_int();
  printf("%s was sucessful.", __func__);
  return 0;
}
