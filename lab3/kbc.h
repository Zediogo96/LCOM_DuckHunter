#include <stdio.h>
#include <lcom/lcf.h>
#include <stdint.h>
#include <lcom/lab3.h>

int (subscribe_kbc)(uint8_t *bit_nr);
int (unsubscribe_kbc)();
int(check_stat_kb)();
int kbc_cmd_read(uint8_t *output);
int kbc_cmd_write(uint8_t command);

