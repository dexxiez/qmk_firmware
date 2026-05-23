#include "bg_cycle.h"
#include "config.h"

const rgb_color bg_colors[NUM_BG_COLORS] = {{RGB_BG_OG}, {RGB_BG_BLUE}, {RGB_BG_PEACH}, {RGB_BG_PINK_2}, {RGB_BG_PURPLE}};

uint8_t current_bg_index = 0;

void cycle_bg_color(void) {
    current_bg_index = (current_bg_index + 1) % NUM_BG_COLORS;
    eeprom_update_byte((uint8_t *)EEPROM_BG_COLOR_INDEX, current_bg_index);
}

void bg_cycle_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    current_bg_index = eeprom_read_byte((uint8_t *)EEPROM_BG_COLOR_INDEX);
    if (current_bg_index >= NUM_BG_COLORS) {
        current_bg_index = 0;
        eeprom_update_byte((uint8_t *)EEPROM_BG_COLOR_INDEX, current_bg_index);
    }
}
