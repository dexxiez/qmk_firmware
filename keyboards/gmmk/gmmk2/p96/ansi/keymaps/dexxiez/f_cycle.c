#include QMK_KEYBOARD_H  // IWYU pragma: keep
#include "f_cycle.h"

static const uint16_t f_cycle_keycodes[CYCLE_OPTIONS] = {KC_F1, KC_F2, KC_F3, KC_F4, KC_F5};
static uint32_t last_cycle_time = 0;

uint8_t current_f_cycle_index = 0;
bool f_cycle_active = false;

void toggle_f_mode(void) {
    f_cycle_active = !f_cycle_active;
    current_f_cycle_index = 0;
}

void f_cycle_send(void) {
    uint32_t now = timer_read32();

    if (timer_elapsed32(last_cycle_time) > CYCLE_TIMEOUT_MS) {
        current_f_cycle_index = 0;
    }

    unregister_mods(MOD_BIT(KC_LSFT));
    tap_code_delay(f_cycle_keycodes[current_f_cycle_index], 80);
    register_mods(MOD_BIT(KC_LSFT));

    current_f_cycle_index = (current_f_cycle_index + 1) % CYCLE_OPTIONS;
    last_cycle_time = now;
}
