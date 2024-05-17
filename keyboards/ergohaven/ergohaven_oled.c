#include "ergohaven.h"
#include "info_config.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
#    ifdef EH_K02
        return OLED_ROTATION_180;
#    else
        return OLED_ROTATION_270;
#    endif
    }
    return rotation;
}

void render_layer_state(void) {
    // Print current mode
    if (strlen(PRODUCT) <= 5)
        oled_write_ln_P(PSTR(PRODUCT), false);
    else // Imperial44 is too long name
        oled_write_ln_P(PSTR("\n"), false);

    oled_write_ln_P(PSTR("v3.3\n"), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_ln_P(PSTR("MODE\n"), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("Mac"), false);
    } else {
        oled_write_ln_P(PSTR("Win"), false);
    }

    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    oled_write_ln_P(PSTR(layer_name(get_highest_layer(layer_state))), false);

    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

__attribute__((weak)) void ergohaven_dark_draw(void) {}

bool oled_task_kb(void) {
    // Defer to the keymap if they want to override
    if (!oled_task_user()) {
        return false;
    }

    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        ergohaven_dark_draw();
    }

    return false;
}

#endif
