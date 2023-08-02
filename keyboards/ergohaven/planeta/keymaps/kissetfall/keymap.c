#include QMK_KEYBOARD_H
#include "kissetfall.h"


float base_sound[][2] = SONG(TERMINAL_SOUND);
float caps_sound[][2] = SONG(CAPS_LOCK_ON_SOUND);

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

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
    PARENTH,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_BASE] = LAYOUT(
         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,                               KC_F7,   KC_F8, KC_F9,   KC_F10, KC_F11,  KC_F12,
         KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,    KC_GRV,
         QK_LEAD, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_ENT,
         KC_ESC,  KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,  KC_COMM, KC_DOT, KC_QUOT, KC_MPLY,
         LALT(KC_LSFT),  KC_LSFT, KC_LCTL, LOWER,   KC_SPC, KC_LBRC,            KC_RBRC, KC_BSPC, RAISE, KC_RSFT, KC_LALT, KC_RGUI 
                                               
      ),
    
      [_LOWER] = LAYOUT(
    
         _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,  _______,
         _______, KC_3,    KC_2,    KC_1,    KC_0,    KC_4,                              KC_7,    KC_6,    KC_5,    KC_9,    KC_8,     _______,
         KC_ENT,  APP_A,   APP_S,   APP_D,   LALT(KC_TAB), APP_G,                        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
         _______, KC_LALT, APP_X,   APP_C,   APP_V,   APP_B,                             _______, PREVWRD, KC_PGDN, KC_PGUP, NEXTWRD,  _______,
                  KC_VOLD, KC_VOLU, _______, _______, _______, _______,         _______, _______, ADJUST, _______, _______, _______ 
    
      ),
    
      [_RAISE] = LAYOUT(
         _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
         _______, _______, KC_AT,   KC_EQL,  KC_PLUS, KC_LPRN,                           KC_RPRN, _______, KC_UNDS, KC_PERC, _______, _______,
         _______, KC_BSLS, KC_DLR,  KC_MINS, KC_HASH, KC_LBRC,                           KC_RBRC, KC_QUES, KC_SCLN, KC_CIRC, KC_EXLM, _______,
         _______, _______, KC_ASTR, KC_COLN, KC_SLSH, KC_LCBR,                           KC_RCBR, KC_PIPE, KC_TILD, KC_AMPR, _______, _______,
                  _______, _______, _______, ADJUST,  _______, _______,         _______, _______, _______, _______, _______, _______ 
      ),
    
      [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, CK_RST,  CK_DOWN, CK_UP,   CK_TOGG, AU_TOGG,                            KC_CAPS, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______                            
       ),
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case NEXTSEN:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING(". ");
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif //AUDIO_ENABLE

        add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
      }
      return false;

    case PREDL:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING("/ ");
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif //AUDIO_ENABLE
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

    case KC_CAPS:
      if (record->event.pressed) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif //AUDIO_ENABLE
      }
      return true; // Let QMK send the enter press/release events
                  
    default:
      return true; // Process all other keycodes normally
  }
    return 0;
};

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(AUDIO_ENABLE)
    static bool is_base_on = false;
if (layer_state_cmp(state, _BASE) != is_base_on) {
        is_base_on = layer_state_cmp(state, _BASE);
        if (is_base_on) {
            stop_all_notes();
        } else {
            PLAY_SONG(base_sound);
        }
    }
#endif
    return state;
}
