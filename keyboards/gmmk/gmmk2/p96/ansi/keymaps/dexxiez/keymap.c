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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum custom_layers {
    _BL,
    _FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: Base Layer (Default Layer)
     */
    [_BL] = LAYOUT(QK_GESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL, KC_PSCR, KC_PGUP, KC_PGDN, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, KC_PENT, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT),

    /* Keymap _FL: Function Layer
     */
    [_FL] = LAYOUT(QK_BOOT, EE_CLR, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MRWD, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI, RGB_HUD, RGB_SPD, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, _______, _______, _______, _______, _______, UC_WIN, _______, _______, _______, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______)};

#define RGB_BG 227, 28, 121

static int MEDIA_KEYS[]      = {5, 6, 7, 8};
static int MEDIA_KEYS_LENGTH = sizeof(MEDIA_KEYS) / sizeof(MEDIA_KEYS[0]);

bool rgb_matrix_indicators_kb(void) {
    // If layer _FL is active
    if (layer_state_is(_FL)) {
        // Background color
        rgb_matrix_set_color_all(RGB_BLACK);

        for (int i = 0; i < MEDIA_KEYS_LENGTH; i++) {
            rgb_matrix_set_color(MEDIA_KEYS[i], RGB_BG);
        }

        return true;
    }

    // Background color
    rgb_matrix_set_color_all(RGB_BG);
    rgb_matrix_set_color(0, RGB_BG); // Escape key because it's not covered by all for some reason

    // Insert key
    rgb_matrix_set_color(13, 0, 255, 0);

    // Delete key
    rgb_matrix_set_color(14, 255, 140, 0);

    return true;
}

void keyboard_post_init_user(void) {
    rgb_matrix_set_color_all(60, 0, 127);
}

