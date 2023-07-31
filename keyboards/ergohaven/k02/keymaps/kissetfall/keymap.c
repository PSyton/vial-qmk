#include QMK_KEYBOARD_H
#include "oled/bongocat.c"
/* #include "oled/luna.c" */

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _FOUR 4
#define _FIVE 5
#define _SIX 6
#define _SEVEN 7
#define _EIGHT 8
#define _NINE 9
#define _TEN 10
#define _ELEVEN 11
#define _TWELVE 12
#define _THIRTEEN 13
#define _FOURTEEN 14
#define _FIFTEEN 15

#define RAISE   MO(_RAISE)
#define LOWER   MO(_LOWER)
#define ADJUST  MO(_ADJUST)
#define PREVWRD LCTL(KC_LEFT)
#define NEXTWRD LCTL(KC_RIGHT)

#define APP_A   LSG(KC_A)
#define APP_S   LSG(KC_S)
#define APP_D   LSG(KC_D)
#define APP_F   LSG(KC_F)
#define APP_G   LSG(KC_G)
#define APP_X   LSG(KC_X)
#define APP_C   LSG(KC_C)
#define APP_V   LSG(KC_V)
#define APP_B   LSG(KC_B)

enum custom_keycodes {
    NEXTSEN = QK_KB,
    PREDL, 
    BRACES,
    PARENTH 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_BASE] = LAYOUT(
         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,                               KC_F7, KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,
         KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,  KC_U,    KC_I,    KC_O,   KC_P,    KC_GRV,
         QK_LEAD, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,  KC_J,    KC_K,    KC_L,   KC_SCLN, KC_ENT,
         KC_ESC,  KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,  KC_M,    KC_COMM, KC_DOT, KC_QUOT, KC_MPLY,
                   LALT(KC_LSFT), KC_LSFT, KC_LCTL, LOWER, KC_SPC,              KC_BSPC, RAISE, KC_RSFT, KC_RALT,  KC_RGUI 
                                               
      ),
    
      [_LOWER] = LAYOUT(
    
         _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,  _______,
         _______, KC_3,    KC_2,    KC_1,    KC_0,    KC_4,                              KC_7,    KC_6,    KC_5,    KC_9,    KC_8,     _______,
         KC_ENT,  APP_A,   APP_S,   APP_D,   LALT(KC_TAB),  APP_G,                       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
         _______, _______, APP_X,   APP_C,   APP_V,   APP_B,                             _______, PREVWRD, KC_PGDN, KC_PGUP, NEXTWRD,  _______,
                           KC_VOLD, KC_VOLU, _______, _______, _______,         _______, ADJUST, _______, _______, _______ 
    
      ),
    
     [_RAISE] = LAYOUT(
         _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
         _______, _______, KC_AT,   KC_EQL,  KC_PLUS, KC_LPRN,                           KC_RPRN, _______, KC_UNDS, KC_PERC, _______, _______,
         _______, KC_BSLS, KC_DLR,  KC_MINS, KC_HASH, KC_LBRC,                           KC_RBRC, KC_QUES, KC_SCLN, KC_CIRC, KC_EXLM, _______,
         _______, _______, KC_ASTR, KC_COLN, KC_SLSH, KC_LCBR,                           KC_RCBR, KC_PIPE, KC_TILD, KC_AMPR, _______, _______,
                           _______, _______, _______, ADJUST,  _______,         _______, _______, _______,  _______, _______ 
      ),
    
      [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            KC_CAPS, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______                            
       ),
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // bongocat
    /* return OLED_ROTATION_270;  // luna */
  }
    else {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
    }
  return rotation;
}

void render_layer_state(void) {
    // Print current mode
    oled_write_ln_P(PSTR("K:02\n"), false);
    /* oled_write_P(PSTR("\n"), false); */
    oled_write_ln_P(PSTR("v2.9\n"), false);
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


// Used to draw on to the oled screen
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
    render_bongocat();  // bongocat
    /* render_luna_status();  // luna */
}

    return false;
}

#endif

// custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        extern uint32_t tap_timer;
        tap_timer = timer_read32();
    }
    switch (keycode) {
    case NEXTSEN:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING(". ");
        add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
      }
      return false;

    case PREDL:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING("/ ");
        add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
      }
      return false;

       case BRACES:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                        SEND_STRING("{}"SS_TAP(X_LEFT));
                    }
                    else {
                        SEND_STRING("[]"SS_TAP(X_LEFT));
                    }
            }
            break;

        case PARENTH:
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            break;
    }
 return true;
} 

void leader_start_user(void) {
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_A)) {
        tap_code16(LGUI(KC_A));
    } else if (leader_sequence_two_keys(KC_A, KC_A)) {
        tap_code16(LAG(KC_A));

    } else if (leader_sequence_one_key(KC_S)) {
        tap_code16(LGUI(KC_S));
    } else if (leader_sequence_two_keys(KC_S, KC_S)) {
        tap_code16(LAG(KC_S));
    
    } else if (leader_sequence_one_key(KC_D)) {
        tap_code16(KC_DEL);
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        tap_code16(LSFT(KC_DEL));

    } else if (leader_sequence_one_key(KC_F)) {
        tap_code16(LGUI(KC_F));
    } else if (leader_sequence_two_keys(KC_F, KC_F)) {
        tap_code16(LAG(KC_F));   

    } else if (leader_sequence_one_key(KC_G)) {
        tap_code16(LGUI(KC_G));
    } else if (leader_sequence_two_keys(KC_G, KC_G)) {
        tap_code16(LAG(KC_G));   

    } else if (leader_sequence_one_key(KC_Q)) {
        tap_code16(LGUI(KC_Q));
    } else if (leader_sequence_two_keys(KC_Q, KC_Q)) {
        tap_code16(LAG(KC_Q));   

    } else if (leader_sequence_one_key(KC_W)) {
        tap_code16(LGUI(KC_W));
    } else if (leader_sequence_two_keys(KC_W, KC_W)) {
        tap_code16(LAG(KC_W));   

    } else if (leader_sequence_one_key(KC_E)) {
        tap_code16(LGUI(KC_E));
    } else if (leader_sequence_two_keys(KC_E, KC_E)) {
        tap_code16(LAG(KC_E));   

    } else if (leader_sequence_one_key(KC_R)) {
        tap_code16(LGUI(KC_R));
    } else if (leader_sequence_two_keys(KC_R, KC_R)) {
        tap_code16(LAG(KC_R));   

    } else if (leader_sequence_one_key(KC_T)) {
        tap_code16(LGUI(KC_T));
    } else if (leader_sequence_two_keys(KC_T, KC_T)) {
        tap_code16(LAG(KC_T));   

    } else if (leader_sequence_one_key(KC_Z)) {
        tap_code16(LGUI(KC_Z));
    } else if (leader_sequence_two_keys(KC_Z, KC_Z)) {
        tap_code16(LAG(KC_Z));   

    } else if (leader_sequence_one_key(KC_X)) {
        tap_code16(LGUI(KC_X));
    } else if (leader_sequence_two_keys(KC_X, KC_X)) {
        tap_code16(LAG(KC_X));   

    } else if (leader_sequence_one_key(KC_C)) {
        tap_code16(LGUI(KC_C));
    } else if (leader_sequence_two_keys(KC_C, KC_C)) {
        tap_code16(LAG(KC_C));   

    } else if (leader_sequence_one_key(KC_V)) {
        tap_code16(LGUI(KC_V));
    } else if (leader_sequence_two_keys(KC_V, KC_V)) {
        tap_code16(LAG(KC_V));   

    } else if (leader_sequence_one_key(KC_B)) {
        tap_code16(LGUI(KC_B));
    } else if (leader_sequence_two_keys(KC_B, KC_B)) {
        tap_code16(LAG(KC_B));   
    
    } else if (leader_sequence_one_key(KC_J)) {
        tap_code16(LGUI(KC_J));
    } else if (leader_sequence_two_keys(KC_J, KC_J)) {
        tap_code16(LAG(KC_J));      

    } else if (leader_sequence_one_key(KC_K)) {
        tap_code16(LGUI(KC_K));
    } else if (leader_sequence_two_keys(KC_K, KC_K)) {
        tap_code16(LAG(KC_K));   

    } else if (leader_sequence_one_key(KC_L)) {
        tap_code16(LGUI(KC_L));
    } else if (leader_sequence_two_keys(KC_L, KC_L)) {
        tap_code16(LAG(KC_L));  

    } else if (leader_sequence_one_key(KC_SCLN)) {
        tap_code16(LGUI(KC_SCLN));
    } else if (leader_sequence_two_keys(KC_SCLN, KC_SCLN)) {
        tap_code16(LAG(KC_SCLN));      

    } else if (leader_sequence_one_key(KC_P)) {
        tap_code16(LGUI(KC_P));
    } else if (leader_sequence_two_keys(KC_P, KC_P)) {
        tap_code16(LAG(KC_P));         
    }
}