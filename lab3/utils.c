#include <lcom/lcf.h>

#include <stdint.h>

#ifdef LAB3
int cnt = 0;
#endif

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  *lsb =  (uint8_t)(val & 0xff);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  *msb = (uint8_t)(val >> 8);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  uint32_t clean_value;
  int error = sys_inb(port,&clean_value);
  *value = (uint8_t) clean_value;
  #ifdef LAB3
  cnt++;
  #endif
  return error;
}
