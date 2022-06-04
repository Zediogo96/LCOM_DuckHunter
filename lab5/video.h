#include <lcom/lcf.h>

int (set_vbe_mode)(uint16_t mode);

uint32_t (build_mask)(uint32_t size, uint32_t pos);

uint32_t (RGB_col)(uint16_t col, uint16_t row, uint32_t first, uint8_t step);

int (draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step);

