#include "ergohaven.h"
#include "info_config.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270; // bongocat, ergohaven_dark/light
                                  // return OLED_ROTATION_270;  // luna
    } else {
        return OLED_ROTATION_270;
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
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        case _FOUR:
            oled_write_P(PSTR("Four\n"), false);
            break;
        case _FIVE:
            oled_write_P(PSTR("Five\n"), false);
            break;
        case _SIX:
            oled_write_P(PSTR("Six\n"), false);
            break;
        case _SEVEN:
            oled_write_P(PSTR("Seven"), false);
            break;
        case _EIGHT:
            oled_write_P(PSTR("Eight"), false);
            break;
        case _NINE:
            oled_write_P(PSTR("Nine\n"), false);
            break;
        case _TEN:
            oled_write_P(PSTR("Ten\n"), false);
            break;
        case _ELEVEN:
            oled_write_P(PSTR("Elevn"), false);
            break;
        case _TWELVE:
            oled_write_P(PSTR("Twlve"), false);
            break;
        case _THIRTEEN:
            oled_write_P(PSTR("Thrtn"), false);
            break;
        case _FOURTEEN:
            oled_write_P(PSTR("Frtn\n"), false);
            break;
        case _FIFTEEN:
            oled_write_P(PSTR("Fiftn"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
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
