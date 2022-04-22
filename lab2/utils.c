#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  *lsb=val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  *msb = (val>>8);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  uint32_t valor = (uint32_t) *(value);
  int ret = sys_inb (port,&valor) ;
  *value = (uint8_t) valor;
  return ret;
}
