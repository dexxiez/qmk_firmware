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
#include "layers.h"
#include "bg_cycle.h"
#include "indicators.h"
////////////// SKIP FORMAT IN NVIM //////////////
//////////////////// :noa w ////////////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: Base Layer (Default Layer)
     */
    [_BL] = LAYOUT(QK_GESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, KC_PSCR, KC_PGDN, KC_PGUP, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_PEQL, KC_PSLS, KC_PAST, KC_PMNS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_P7, KC_P8, KC_P9, KC_PPLS, QK_GESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, KC_PENT, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT),

    /* Keymap _FL: Function Layer
     */
    [_FL] = LAYOUT(QK_BOOT, EE_CLR, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MRWD, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NUM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, CUSTOM_L, _______, _______, _______, _______, _______, _______, _______, RGB_HUI, RGB_HUD, RGB_SPD, RGB_SPI, QK_BOOT, _______, _______, _______, _______, _______, _______, RGB_VAI, _______, _______, _______, _______, _______, UC_WIN, _______, _______, _______, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______)};

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        indicators_set_lock_state(led_state.num_lock, led_state.caps_lock);
    }
    return res;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CUSTOM_L: // Your custom keycode for cycling
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

void keyboard_post_init_user(void) {
    bg_cycle_init();

    rgb_matrix_set_color_all(60, 0, 127);

    indicators_init_lock_state();
}
