#include "video_gr.h"

static void *video_mem; /* Process (virtual) address to which VRAM is mapped */
static void *video_buffer;

static unsigned h_res; /* Horizontal resolution in pixels */
static unsigned v_res; /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel;
/* static enum xpm_image_type img_type; */
static unsigned phys_base_ptr;

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

  vbe_mode_info_t vmi_p;

  vbe_get_mode_info(mode, &vmi_p);

  /* switch (mode) {
      case 
  } */

  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;

  bits_per_pixel = vmi_p.BitsPerPixel;
  bytes_per_pixel = bits_per_pixel != 15 ? bits_per_pixel / 8 : 2;
  phys_base_ptr = vmi_p.PhysBasePtr;

  printf("h_res: %d    v_res: %d    bites_per_pixel: %d\n", h_res, v_res, bits_per_pixel);
  
  unsigned int vram_size = h_res * v_res * bytes_per_pixel;

  video_buffer = (uint8_t *) malloc(vram_size);
  memset(video_buffer, 0, vram_size);

  video_mem = vbe_map_vram(phys_base_ptr, vram_size);

  if (video_mem == NULL) {
      printf("Failed to map vram\n");
      return NULL;
  }
  
  if (vbe_set_mode(mode)) {
      printf("vbe_set_mode failed\n");
      return NULL;
  }
  return video_mem; 
}
