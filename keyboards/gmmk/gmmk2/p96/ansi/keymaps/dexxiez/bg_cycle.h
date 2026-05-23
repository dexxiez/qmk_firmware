#ifndef DEXXIEZ_BG_CYCLE_H
#define DEXXIEZ_BG_CYCLE_H

#include QMK_KEYBOARD_H
#include "../../structs.h"

#define NUM_BG_COLORS 5

extern const rgb_color bg_colors[NUM_BG_COLORS];
extern uint8_t         current_bg_index;

// Expand to the r, g, b triple of the active background color.
// Intended for direct use as the last 3 args to rgb_matrix_set_color().
#define CURRENT_RGB_BG bg_colors[current_bg_index].r, bg_colors[current_bg_index].g, bg_colors[current_bg_index].b

void cycle_bg_color(void);
void bg_cycle_init(void);

#endif
