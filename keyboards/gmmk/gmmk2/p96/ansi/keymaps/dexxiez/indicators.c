#include "indicators.h"
#include "bg_cycle.h"
#include "f_cycle.h"
#include "config.h"
#include "layers.h"

static int MEDIA_KEYS[]      = {MEDIA_KEYS_RANGE};
static int MEDIA_KEYS_LENGTH = sizeof(MEDIA_KEYS) / sizeof(MEDIA_KEYS[0]);

static bool numlock_active  = false;
static bool capslock_active = false;

static void handle_keystates(void) {
    if (!numlock_active) {
        rgb_matrix_set_color(NUMLOCK_KEY, RGB_RED);
    }

    if (capslock_active) {
        rgb_matrix_set_color(CAPSLOCK_KEY, RGB_RED);
    }
}

void indicators_set_lock_state(bool num, bool caps) {
    numlock_active  = num;
    capslock_active = caps;
    handle_keystates();
}

void indicators_init_lock_state(void) {
    numlock_active  = host_keyboard_led_state().num_lock;
    capslock_active = host_keyboard_led_state().caps_lock;
    handle_keystates();
}

bool rgb_matrix_indicators_kb(void) {
    if (layer_state_is(_FL)) {
        rgb_matrix_set_color_all(RGB_BLACK);

        for (int i = 0; i < MEDIA_KEYS_LENGTH; i++) {
            rgb_matrix_set_color(MEDIA_KEYS[i], CURRENT_RGB_BG);
        }

        rgb_matrix_set_color(CAPSLOCK_KEY, CURRENT_RGB_BG);
        rgb_matrix_set_color(L_KEY, CURRENT_RGB_BG);

        if (f_cycle_active) {
            rgb_matrix_set_color(LSHIFT_KEY, RGB_WHITE);
            rgb_matrix_set_color(TAB_KEY, RGB_WHITE);
        }

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

    rgb_matrix_set_color_all(CURRENT_RGB_BG);
    rgb_matrix_set_color(ESC_KEY, CURRENT_RGB_BG);

    rgb_matrix_set_color(INSERT_KEY, RGB_INSERT);
    rgb_matrix_set_color(DELETE_KEY, RGB_DELETE);

    if (f_cycle_active) {
        rgb_matrix_set_color(LSHIFT_KEY, RGB_GREY);
        rgb_matrix_set_color(TAB_KEY, RGB_GREY);
    }

    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    handle_keystates();
    return true;
}
