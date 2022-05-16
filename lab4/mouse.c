
#include <mouse.h>

int hookID;
extern uint8_t out_byte;

int mouse_subscribe_int(uint8_t *bit_no) {
  hookID = MOUSE_IRQ;
  *bit_no = (uint8_t) hookID;
  if (sys_irqsetpolicy(hookID, IRQ_REENABLE | IRQ_EXCLUSIVE, &hookID) != 0) {
    printf("%s sys_irqsetpolicy() failed \n", __func__);
    return 1;
  }
  return 0;
}

int mouse_unsubscribe_int() {
  if (sys_irqrmpolicy(&hookID) != 0) {
    printf("%s: sys_irqrmpolicy() failed\n", __func__);
    return 1;
  }
  return 0;
}

void(mouse_ih)() {
  while (true) {
    if (kbc_read_outb() == 0) {
      break;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

/**
 * @brief This function is used to process the packets, see slide 32 of 06-Mouse.pdf for more information
 *
 * @param bytes
 * @return struct packet
 */
struct packet process_packets(uint8_t *bytes) {
  struct packet pp;

  for (int i = 0; i < 3; ++i) pp.bytes[i] = bytes[i];

  pp.lb = bytes[0] & MOUSE_LB_CLICK; // bit 0
  pp.rb = bytes[0] & MOUSE_RB_CLICK; // bit 1
  pp.mb = bytes[0] & MOUSE_MB_CLICK; // bit 2
  /** BIT 3 is ignored? **/
  pp.x_ov = bytes[0] & MOUSE_X_OVFL; // bit 6
  pp.y_ov = bytes[0] & MOUSE_Y_OVFL; // bit 7

  pp.delta_x = bytes[1];
  pp.delta_y = bytes[2];

  /** Special to convert argument to complement of 2, depending on the sign of X and Y **/
  bool msb_x = bytes[0] & MOUSE_X_SIGN;
  bool msb_y = bytes[0] & MOUSE_Y_SIGN;
  for (int i = 8; i < 16; ++i) pp.delta_x += (msb_x << i);
  for (int i = 8; i < 16; ++i) pp.delta_y += (msb_y << i);

  return pp;
}

int mouse_disable_reporting() {
  for (int i = 0; i < 5; ++i) {
    /** It's the same command as the keyboard one **/
    if (kbc_issue_command(WRITE_BYTE_TO_MOUSE, KBC_CMD_REG)) return 1; 
    if (kbc_issue_command(DISABLE_DATA_REPORTING, KBC_OUTPUT_BUF)) return 1;
    if (util_sys_inb(KBC_OUTPUT_BUF, &out_byte)) return 1;
    if (out_byte == ACK) return 0;
    tickdelay(micros_to_ticks(DELAY_US));
  }
  printf("%s: disable mouse data reporting failed \n", __func__);
  return 1;
}
