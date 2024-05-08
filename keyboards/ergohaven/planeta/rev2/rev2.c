#include "display.h"


/* Caps Lock processing */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res && is_display_enabled()) {
        display_process_caps(led_state.caps_lock);
    }

    return res;
}

void housekeeping_task_kb(void) {
    if (is_display_enabled()) {
        display_housekeeping_task();
    }

    housekeeping_task_user();
}

void keyboard_post_init_user(void) {
    display_init_kb();
    writePinHigh(GP18);
}
