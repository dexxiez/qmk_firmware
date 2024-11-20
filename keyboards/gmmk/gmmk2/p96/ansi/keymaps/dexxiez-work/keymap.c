/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "config.h"
#include "../../structs.h"
////////////// SKIP FORMAT IN NVIM //////////////
//////////////////// :noa w ////////////////////


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum custom_layers {
    _BL,
    _FL,
};

enum custom_keycodes {
    CUSTOM_L = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: Base Layer (Default Layer)
     */
[_BL] = LAYOUT(
  QK_GESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_DEL,   KC_PSCR,  KC_PGDN,  KC_PGUP,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_PEQL,  KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  QK_GESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT),

    /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT(
  QK_BOOT,  EE_CLR,  KC_WHOM,  KC_CALC,  KC_MSEL,  KC_MPRV,  KC_MRWD,  KC_MPLY,  KC_MSTP,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_NUM,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  CUSTOM_L, _______,  _______,  _______,             _______,  _______,  _______,
  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,   _______,  _______,  _______,  _______,
  _______,  UC_WIN,   _______,                      _______,                                _______,  _______,  _______,  RGB_RMOD,  RGB_VAD,  RGB_MOD,  _______,  _______)
};



static int MEDIA_KEYS[]      = {MEDIA_KEYS_RANGE};
static int MEDIA_KEYS_LENGTH = sizeof(MEDIA_KEYS) / sizeof(MEDIA_KEYS[0]);

bool numlock_active = false;
bool capslock_active = false;

static const rgb_color bg_colors[] = {
    {RGB_BG_BLUE},
    {RGB_BG_PEACH},
    {RGB_BG_PINK_2},
    {RGB_BG_PURPLE}
};

// BG Cycling
#define NUM_BG_COLORS (sizeof(bg_colors) / sizeof(bg_colors[0]))
static uint8_t current_bg_index = 0;
#define CURRENT_RGB_BG bg_colors[current_bg_index].r, bg_colors[current_bg_index].g, bg_colors[current_bg_index].b

void cycle_bg_color(void) {
    current_bg_index = (current_bg_index + 1) % NUM_BG_COLORS;
    eeprom_update_byte((uint8_t*)EEPROM_BG_COLOR_INDEX, current_bg_index);
}

// END BG Cycling

void handle_keystates(void){
    if (!numlock_active){
        rgb_matrix_set_color(NUMLOCK_KEY, RGB_RED);
    }

    if (capslock_active){
        rgb_matrix_set_color(CAPSLOCK_KEY, RGB_RED);
    }
}

bool rgb_matrix_indicators_kb(void) {
    // If layer _FL is active
    if (layer_state_is(_FL)) {
        // Background color
        rgb_matrix_set_color_all(RGB_BLACK);

        for (int i = 0; i < MEDIA_KEYS_LENGTH; i++) {
            rgb_matrix_set_color(MEDIA_KEYS[i], CURRENT_RGB_BG);
        }

        rgb_matrix_set_color(CAPSLOCK_KEY, CURRENT_RGB_BG);
        rgb_matrix_set_color(L_KEY, CURRENT_RGB_BG);

        switch (current_bg_index) {
            case 0:
                rgb_matrix_set_color(NUMPAD1_KEY, RGB_WHITE);
                break;
            case 1:
                rgb_matrix_set_color(NUMPAD2_KEY, RGB_WHITE);
                break;
            case 2:
                rgb_matrix_set_color(NUMPAD3_KEY, RGB_WHITE);
                break;
            case 3:
                rgb_matrix_set_color(NUMPAD4_KEY, RGB_WHITE);
                break;
            case 4:
                rgb_matrix_set_color(NUMPAD5_KEY, RGB_WHITE);
                break;
            case 5:
                rgb_matrix_set_color(NUMPAD6_KEY, RGB_WHITE);
                break;

        }
        return true;
    }

    // Background color
    rgb_matrix_set_color_all(CURRENT_RGB_BG);
    rgb_matrix_set_color(ESC_KEY, CURRENT_RGB_BG); // Escape key because it's not covered by all for some reason

    // Insert key
    rgb_matrix_set_color(INSERT_KEY, RGB_INSERT);

    // Delete key
    rgb_matrix_set_color(DELETE_KEY, RGB_DELETE);

    return true;
}

bool led_update_kb(led_t led_state){
    bool res = led_update_user(led_state);
    if(res){
        numlock_active = led_state.num_lock;
        capslock_active = led_state.caps_lock;
        handle_keystates();
    }
    return res;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CUSTOM_L:  // Your custom keycode for cycling
        if (record->event.pressed) {
            if (layer_state_is(_FL)) {
                cycle_bg_color();
                return false;
            }
        }
        break;
    }
    return true;
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    handle_keystates();
    return true;
}

void keyboard_post_init_user(void) {
    // Initialize EEPROM if needed
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    // Load saved color index from our specific address
    current_bg_index = eeprom_read_byte((uint8_t*)EEPROM_BG_COLOR_INDEX);
    if (current_bg_index >= NUM_BG_COLORS) {
        current_bg_index = 0;  // Reset if invalid
        eeprom_update_byte((uint8_t*)EEPROM_BG_COLOR_INDEX, current_bg_index);
    }


    rgb_matrix_set_color_all(60, 0, 127);

    numlock_active = host_keyboard_led_state().num_lock;
    capslock_active = host_keyboard_led_state().caps_lock;
    handle_keystates();
}

