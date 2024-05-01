#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "oled/ergohaven_dark.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BASE] = LAYOUT(
          KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
          KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_RGUI,
          KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT,  KC_RSFT,
                                             KC_LCTL, LOWER,   KC_SPC, KC_MUTE,    KC_HOME, KC_ENT,  RAISE,   KC_RALT
        ),

        [_LOWER] = LAYOUT(
         _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     _______,
         _______, KC_HOME, KC_INS,  KC_DEL,  KC_END,  LANG,                                          _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
         _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_PSCR,                                       KC_CAPS, PREVWRD, KC_PGDN, KC_PGUP, NEXTWRD,  _______,
                                             _______, _______, _______, _______,   _______, _______, ADJUST,  _______
        ),

        [_RAISE] = LAYOUT(
         _______, KC_AT,   KC_LT,   KC_EQL,  KC_GT,   KC_GRV,                                        KC_CIRC, KC_LBRC, KC_UNDS, KC_RBRC, _______,  _______,
         _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                                       KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,  _______,
         _______, KC_HASH, KC_ASTR, KC_COLN, KC_SLSH, _______,                                       _______, KC_PIPE, KC_TILD, KC_AMPR, KC_DLR,   _______,
                                             _______, ADJUST,  _______, _______,   _______, _______, _______, _______
        ),

      [_ADJUST] = LAYOUT(

        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
        _______, _______, _______, _______, _______, _______,                                        _______, KC_VOLD, KC_MUTE, _______, KC_VOLU,  _______,
        _______, DM_REC1, DM_RSTP, DM_PLY1, _______, CG_TOGG,                                        _______, KC_MPRV, KC_MPLY, _______, KC_MNXT,  _______,
                                            _______, _______,  _______, _______,   _______, _______, _______, _______

       ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGDN, KC_PGDN)},
  [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
  [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
  [3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // bongocat, ergohaven_dark/light
    // return OLED_ROTATION_270;  // luna
     }
    else {
    return OLED_ROTATION_270;
    }
  return rotation;
}

void render_layer_state(void) {
    // Print current mode
    //oled_write_ln_P(PSTR("\n"), false);
    oled_write_P(PSTR("\n"), false);
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
    // oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}


// Used to draw on to the oled screen
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        ergohaven_dark_draw();
}
    return false;
}

#endif
