#ifndef __VIDEO_GR_H__
#define __VIDEO_GR_H__

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <minix/sysutil.h>

// BIOS SERVICES
#define BIOS_VID_CARD 0x10

// AH consts
#define VBE_CALL 0x4F

// FUNCTIONS
#define SET_VBE_MODE 0x02
#define GET_VBE_MODE_INFO 0x01
#define GET_VBE_CONTROLLER_INFO 0x00

// Graphics modes
#define MODE_1024x768_INDEX 0x105
#define MODE_640x480_DIRECT 0x110
#define MODE_800x600_DIRECT 0x115
#define MODE_1280x1024_DIRECT 0x11A
#define MODE_1152x864_DIRECT 0x14C
#define MODE_CGA 0x03

// BUFFER MODEL

#define LINEAR_BUFFER BIT(14);

/**
 * @brief Initializes the graphics in a given mode.
 * Extracts information from the vbe and passes it to static variables.
 * Maps the video memory and also allocates memory for the double buffer.
 * @param mode
 * @return video_mem: pointer to the video memory
 */
void *(vg_init) (uint16_t mode);

/**
 * @brief Changes a pixel color in the double buffer by using memcpy()
 * @param x X position of the pixel pointer
 * @param y Y position of the pixel pointer
 * @param color
 * @return 0 if sucessful, 1 otherwise
 */
int(change_pixel_color)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line, with a given length and color
 * @param x x coordinate of the start (top) of the line
 * @param y y coordinate of the start (top) of the line
 * @param len
 * @param color
 * @return 0 if sucessful, 1 otherwise
 */
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a vertical line, with a given length and color
 * @param x x coordinate of the start (left) of the line
 * @param y y coordinate of the start (left) of the line
 * @param len
 * @param color
 * @return 0 if sucessful, 1 otherwise
 */
int (vg_draw_vline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle with a given width, height and color, with it's top left corner at coordinates (x,y)
 * @param x x coordinate of the top left corner of the rectangle
 * @param y y coordinate of the top left corner of the rectangle
 * @param width
 * @param height
 * @param color
 * @return 0 if sucessful, 1 otherwise
 */
int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Draws a xpm image
 * @param x x coordinate of the top left corner of the image
 * @param y y coordinate of the top left corner of the image
 * @return 0 if sucessful, 1 otherwise
 */
int(vg_draw_image)(xpm_image_t img, uint16_t x, uint16_t y);

/**
 * @brief Get the video mem pointer
 *
 * @return void*
 */
void *get_video_mem();

/**
 * @brief Get the double buffer pointer
 *
 * @return void*
 */
void *get_double_buffer();

/**
 * @brief Copy the contents from the double buffer (that receives the input) into the main buffer (that is being displayed)
 * This insure great perfomance and no-flickering of the image
 */
void copyDoubleBufferToMain();

/**
 * @brief Get the h_res value
 *
 * @return int
 */
int get_h_res();

/**
 * @brief Get the v_res value
 *
 * @return int
 */
int get_v_res();

/**
 * @brief Get the bytes per pixel object
 *
 * @return unsigned
 */
unsigned get_bytes_per_pixel();

#endif // __VIDEO_GR_H__
