// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "video.h"
#define KBC_ST_REG 0x64
#define KBC_CMD_REG 0x64
#define KB_STATUS_REG 0x64
#define KB_OUT_BUFF 0x60
#define KBC_ARG_REG 0x60
#define ESC 0x81
#define IRQ_KB 1
#define TWO_BYTE 0xe0
#define READ_CMD 0x20
#define WRITE_CMD 0x60

#define WAIT_KBC 20000
int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  uint32_t clean_value;
  int error = sys_inb(port,&clean_value);
  *value = (uint8_t) clean_value;
  return error;
}


// Any header files included below this line should have been created by you
int hoookid = IRQ_KB;
bool two_byte_scan_code = false;
uint8_t scancode[3];

int (subscribe_kbc)(uint8_t *bit_nr){
    *bit_nr = hoookid;
    if(sys_irqsetpolicy(IRQ_KB,IRQ_REENABLE | IRQ_EXCLUSIVE,&hoookid))
    {
        return 1;
    }
    return 0;
}

int (unsubscribe_kbc)()
{
    if(sys_irqrmpolicy(&hoookid))
    {
        return 1;
    }
    return 0;
}
void (kbc_ih)(){
    scancode[2] = 0;
    uint8_t scan_code;
    /*
    if(check_stat_kb())
    {
        return; //error in status register
    }
    */
    if(util_sys_inb(KB_OUT_BUFF,&scan_code))
    {
        return; // error reading scan code
    }
    if(scan_code == TWO_BYTE)
    {
        two_byte_scan_code = true;
        scancode[0] = scan_code;
    }
    else if(two_byte_scan_code){
        scancode[1] = scan_code;
        scancode[2] = 1;
        two_byte_scan_code = false;
    }
    else{
        scancode[0] = scan_code;
        scancode[2] = 2;
    }
    return; 
}

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
 

  vg_init(mode);
  sleep(delay);
  vg_exit();
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){


  vg_init(mode);
  for(int i = 0; i < height;i++)
  {
      vg_draw_hline(x,y,width,color);
      y++;
  }
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
  
  vg_exit();
  
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  vg_init(mode);
  draw_pattern(no_rectangles,first,step);

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
  

  
  vg_exit();
  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
