#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  *lsb = val;
  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  *msb = (val >> 8);
  return 1;
}

int (util_sys_inb)(int port, uint8_t *value) {
  
    uint32_t value32;

    int status = sys_inb(port, &value32);
    *value = (uint8_t) value32; // Only assigns the first 8 bits

    return status;
}
