#ifndef DEXXIEZ_INDICATORS_H
#define DEXXIEZ_INDICATORS_H

#include QMK_KEYBOARD_H

void indicators_set_lock_state(bool num, bool caps);
void indicators_init_lock_state(void);

#endif
