#ifndef DEXXIEZ_F_CYCLE_H
#define DEXXIEZ_F_CYCLE_H

#include <stdbool.h>
#include <stdint.h>

#define CYCLE_TIMEOUT_MS 2000
#define CYCLE_OPTIONS 4

extern uint8_t current_f_cycle_index;
extern bool    f_cycle_active;

void toggle_f_mode(void);
void f_cycle_send(void);

#endif
