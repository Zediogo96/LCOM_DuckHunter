#include <lcom/lcf.h>
#include <stdint.h>
#include <kbc.h>
#include "var.h"
#include <lcom/lab3.h>

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

int kbc_cmd_write(uint8_t command) {
  sys_outb(KBC_CMD_REG, WRITE_CMD);
  sys_outb(KBC_ARG_REG, command);
  return 0;
}

int kbc_cmd_read(uint8_t *output){
  sys_outb(KBC_CMD_REG, READ_CMD);
  util_sys_inb(KB_OUT_BUFF, output);
  return 0;
}

void (kbc_ih)(){
    scancode[2] = 0;
    uint8_t scan_code;
    
    if(check_stat_kb())
    {
        return; //error in status register
    }
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
        printf("entrou");
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

int (check_stat_kb)(){

    uint8_t status;
    if(util_sys_inb(KB_STATUS_REG,&status))
    {
        printf("Could not read status from KB");
        return 1;
    }
    if(status & (Parity | Timeout))//checks if communication had any errors
    {
        printf("Communication error");
        return 1;
    }
    if(status & (Aux))
    {
        printf("Mouse data found");
        return 1;
    }
    if(status & OBF)
    {
        return 0;//data ready for reading
    }
    return 1;// no data to read
}

