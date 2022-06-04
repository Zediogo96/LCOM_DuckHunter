#include <lcom/lcf.h>
#include "video.h"

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static uint16_t x_res;
static uint16_t y_res;
static uint16_t bytes_per_pixel;
static uint16_t bytes_per_row;
static uint16_t bits_per_pixel;
static uint16_t g_mask_size;
static uint16_t r_mask_size;
static uint16_t b_mask_size;
static uint16_t b_pos;
static uint16_t g_pos;
static uint16_t r_pos;

int set_vbe_mode(uint16_t mode){

    reg86_t r;
    memset((void *) &r, 0, sizeof(r));
    r.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
    r.bx = 1<<14|mode; // set bit 14: linear framebuffer
    r.intno = 0x10;
    if( sys_int86(&r) != OK ) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return 1;
    } 
    return 0;
}

void *(vg_init)(uint16_t mode) {

    vbe_mode_info_t info;

    
    vbe_get_mode_info(mode,&info);


    x_res = info.XResolution;
    y_res = info.YResolution;
    bits_per_pixel = info.BitsPerPixel;
    bytes_per_pixel = info.BitsPerPixel / 8;
    bytes_per_row = (info.XResolution * info.BitsPerPixel) / 8; 
    g_mask_size = info.GreenMaskSize;
    r_mask_size = info.RedMaskSize;
    b_mask_size = info.BlueMaskSize;
    g_pos = info.GreenFieldPosition;
    b_pos = info.BlueFieldPosition;
    r_pos = info.RedFieldPosition;
    
    int r;
    struct minix_mem_range mr; /* physical memory range */
    unsigned int vram_base; /* VRAM’s physical addresss */
    unsigned int vram_size; /* VRAM’s size, but you can use

    the frame-buffer size, instead */
    vram_base = info.PhysBasePtr;
    
    vram_size = (info.XResolution * info.YResolution * info.BitsPerPixel) / 8;

    

    /* Allow memory mapping */
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    /* Map memory */
    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
   
    set_vbe_mode(mode);

    if(video_mem == MAP_FAILED)
        panic("couldn’t map video memory");
        
    return video_mem;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){


    char * p;
    p = video_mem + (bytes_per_pixel * x) + (bytes_per_row * y);
    for(int i = 0; i < len; i++)
    {
       memcpy(p,&color,bytes_per_pixel);
       p += bytes_per_pixel;
    }
    
    return 0;
    
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){

    for(int i = 0; i<height;i++)
    {
        vg_draw_hline(x,y,width,color);
        y++;
    }
    return 0;
}
uint32_t (build_mask)(uint32_t size, uint32_t pos) {
  uint32_t mask = 0x1;
  for (uint32_t i = 0; i < size - 1; i++) {
    mask = (mask << 1) + 1;
  }
  return mask << pos;
}
uint32_t (RGB_col)(uint16_t col, uint16_t row, uint32_t first, uint8_t step) {
  uint32_t r, g, b, r_mask, g_mask, b_mask;
  
  r_mask = build_mask(r_mask_size, r_pos);
  g_mask = build_mask(g_mask_size, g_pos);
  b_mask = build_mask(b_mask_size, b_pos);
  

  r = ((((first & r_mask) >> r_pos) + col * step) % (1 << r_mask_size)) << r_pos;
  g = ((((first & g_mask) >> g_pos) + row * step) % (1 << g_mask_size)) << g_pos;
  b = (((first & b_mask) + (col + row) * step) % (1 << b_mask_size)) << b_pos;

  return r | g | b;
}

int (draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint16_t width = x_res / no_rectangles;
  uint16_t height = y_res / no_rectangles;

  for (uint16_t row = 0; row < no_rectangles; row++) {
    for (uint16_t col = 0; col < no_rectangles; col++) {
      uint32_t color = 0;
      if(bytes_per_pixel==1)
      {
          color = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
      }else{
          color = RGB_col(col, row, first, step);
      }
      
      
      // printf("%d\n", color);
       vg_draw_rectangle(col*width,row*height,width,height,color);
    }
  }
  return 0;
}






