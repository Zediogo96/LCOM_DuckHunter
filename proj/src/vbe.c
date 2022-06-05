#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "Include/vbe.h"

int vbe_call(struct reg86 * r) {
  /* Make the BIOS call */
  if (sys_int86(r) != 0) {
    printf("\tvbe_set_mode: sys_int86() failed \n");
    return 1;
  }

  switch (r->ah) {
    case AH_CALL_FAILED: printf("BIOS call failed \n"); return 1;
    case AH_NOT_SUPPORTED_CONF: printf("BIOS not supported config \n"); return 1;
    case AH_NOT_SUPPORTED_MODE: printf("BIOS not supported mode\n"); return 1;
  }

  return 0;
}

void * vbe_map_vram(unsigned int phys_base_ptr, unsigned int vram_size) {

  // struct minix_mem_range {
  //   phys_bytes mr_base; /* Lowest memory address in range */
  //   phys_bytes mr_limit; /* Highest memory address in range */
  // };

  struct minix_mem_range mr;
  unsigned int vram_base = phys_base_ptr;
  int r;

  /** ALLOW MEMORY MAPPING */
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  printf("mapped VRAM base: 0x%x size:%d limit 0x%x", mr.mr_base, vram_size, mr.mr_limit);

  if (0 != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* MAP MEMORY */
  void * video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED)
    panic("couldn't map video memory");
  return video_mem;
}

int vbe_set_mode(uint16_t mode) {
  struct reg86 r;
  memset(&r, 0, sizeof(r));
  r.intno = BIOS_VID_CARD;
  r.ah = VBE_CALL;
  r.al = SET_VBE_MODE;
  r.bx = mode | LINEAR_BUFFER;

  if (vbe_call(&r)) {
    printf("VBE call failed");
    return 1;
  }
  return 0;
}
