#include "Include/video_gr.h"

static void *video_mem; /* Process (virtual) address to which VRAM is mapped */
static void *double_buff;

static unsigned h_res;          /* Horizontal resolution in pixels */
static unsigned v_res;          /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel;
/* static enum xpm_image_type img_type;
static unsigned phys_base_ptr; */
static vbe_mode_info_t inf;

/**
 * @file video_gr.c
 * @author your name (you@domain.com)
 * @brief Initializes the video module in graphics mode.
        Uses the VBE INT 0x10 interface to set the desired graphics mode using a linear frame buffer, maps VRAM to the process' address space and initializes static global variables
        with the resolution of the screen, and the color depth (i.e the no. of bits per pixel).
        Initially, you should call function vbe_get_mode_info() provided by the LCF, to get this information. Later, you can implement your own version of this function.
 * @version 0.1
 * @date 2022-05-16
 *
 * @copyright Copyright (c) 2022
 *
 */

void *(vg_init) (uint16_t mode) {
  if (vbe_get_mode_info(mode, &inf) != 0) { // if Operation fail
    printf("vg_init(): failed to get mode \n");
    return NULL;
  }

  struct reg86 r86;
  int r;
  struct minix_mem_range mr;
  static unsigned int vram_base;
  static unsigned int vram_size;
  h_res = inf.XResolution;
  v_res = inf.YResolution;
  bits_per_pixel = inf.BitsPerPixel;
  bytes_per_pixel = (bits_per_pixel + 7) / 8;

  vram_base = inf.PhysBasePtr;
  vram_size = h_res * v_res * bytes_per_pixel;

  double_buff = malloc(vram_size);

  /* Allow memory mapping */
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return NULL;
  }
  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    panic("couldn't map video memory");
    return NULL;
  }

  memset(&r86, 0, sizeof(r86));

  r86.ax = 0x4F02;
  r86.bx = BIT(14) | mode;
  r86.intno = 0x10;

  if (sys_int86(&r86) != 0) { // if Operation fail
    printf("vg_init(): sys_int86() failed \n");
    return NULL;
  }

  return video_mem;
}

int(change_pixel_color)(uint16_t x, uint16_t y, uint32_t color) {

  if (x >= h_res || y >= v_res) {
    return 1;
  }

  uint8_t *pixel_pointer;

  pixel_pointer = (uint8_t *) double_buff + (x * bytes_per_pixel) + (y * h_res * bytes_per_pixel);
  uint8_t change;

  for (unsigned i = 0; i < bytes_per_pixel; i++) {
    change = color & 0xFF;
    *(pixel_pointer + i) = change;
    color = color >> 8;
  }

  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    if (change_pixel_color(x + i, y, color) != 0) {
      return 1;
    }
  }
  return 0;
}

int(vg_draw_vline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    if (change_pixel_color(x, y + i, color) != 0) {
      return 1;
    }
  }
  return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + i, width, color) != 0) {
      return 1;
    }
  }
  return 0;
}


int (vg_draw_image)(xpm_image_t img, uint16_t x, uint16_t y){

  uint32_t transparent = xpm_transparency_color(XPM_8_8_8_8);
  uint32_t* color = (uint32_t*)img.bytes;

  for(int i=0; i<img.height; i++){
    for(int j=0; j<img.width; j++){
      if(*color!=transparent){
        if(change_pixel_color(x + j,y + i, *color)!=0){
          return 1;
        }
      }
      
      color++;
    }
  }

  return 0;
}

char * get_video_mem() {
  return (char*) video_mem;
}

char * get_double_buffer() {
  return (char *) double_buff;
}

void copyDoubleBufferToMain() {
  memcpy(video_mem, double_buff, h_res * v_res * bytes_per_pixel);
}

int get_h_res() {
  return h_res;
}

int get_v_res() {
  return v_res;
}

unsigned get_bits_per_pixel() {
  return bits_per_pixel;
}

unsigned get_bytes_per_pixel() {
  return bytes_per_pixel;
}
