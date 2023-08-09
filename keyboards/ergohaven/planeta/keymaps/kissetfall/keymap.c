#include QMK_KEYBOARD_H
#include "kissetfall.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_BASE] = LAYOUT(
         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,                               KC_F7,   KC_F8, KC_F9,   KC_F10, KC_F11,  KC_F12,
         KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,    KC_GRV,
         KC_LALT, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_ENT,
         KC_ESC,  KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,  KC_COMM, KC_DOT, KC_QUOT, KC_MPLY,
         KC_VOLD, KC_VOLU, KC_LCTL, LOWER,  KC_SPC, KC_LBRC,                    KC_RBRC, KC_BSPC, RAISE, KC_RSFT, RALT(KC_RSFT), KC_RGUI 
                                               
      ),
    
      [_LOWER] = LAYOUT(
    
         _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______,  _______,
         _______, KC_3,    KC_2,    KC_1,    KC_0,    KC_4,                              KC_7,    KC_6,    KC_5,    KC_9,    KC_8,     _______,
         KC_ENT,  KC_LSFT, APP_S,   KC_DEL,  ALT_TAB, APP_G,                             KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
         _______, _______, _______, APP_C,   APP_V,   APP_B,                             KC_END,  PREVWRD, KC_PGDN, KC_PGUP, NEXTWRD,  _______,
                  KC_MPRV, KC_MNXT, _______, _______, _______, _______,         _______, _______, ADJUST, _______, _______, _______ 
    
      ),
    
      [_RAISE] = LAYOUT(
         _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
         _______, _______, KC_AT,   KC_EQL,  KC_PLUS, KC_LPRN,                           KC_RPRN, KC_TILD, KC_UNDS, KC_PERC, _______, _______,
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
       )
};

// bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//     switch (keycode) {
//     case NEXTSEN:  // Next sentence macro.
//       if (record->event.pressed) {
//         SEND_STRING(". ");
//     #ifdef AUDIO_ENABLE
//         PLAY_SONG(caps_sound);
//     #endif //AUDIO_ENABLE

//         add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
//       }
//       return false;

//     case PREDL:  // Next sentence macro.
//       if (record->event.pressed) {
//         SEND_STRING("/ ");
//     #ifdef AUDIO_ENABLE
//         PLAY_SONG(caps_sound);
//     #endif //AUDIO_ENABLE
//         add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
//       }
//       return false;

//        case BRACES:
//             if (record->event.pressed) {
//                 uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
//                     if (shifted) {
//                         unregister_code(KC_LSFT);
//                         unregister_code(KC_RSFT);
//                         SEND_STRING("{}"SS_TAP(X_LEFT));
//                     }
//                     else {
//                         SEND_STRING("[]"SS_TAP(X_LEFT));
//                     }
//             }
//             break;

//     case PARENTH:
//             if (record->event.pressed) {
//                 SEND_STRING("()");
//                 tap_code(KC_LEFT);
//             }
//           break;

//     case KC_CAPS:
//       if (record->event.pressed) {
//     #ifdef AUDIO_ENABLE
//         PLAY_SONG(caps_sound);
//     #endif //AUDIO_ENABLE
//       }
//       return true; // Let QMK send the enter press/release events
                  
//     default:
//       return true; // Process all other keycodes normally
//   }
//     return 0;
// };

// layer_state_t layer_state_set_user(layer_state_t state) {
// #if defined(AUDIO_ENABLE)
//     static bool is_base_on = false;
// if (layer_state_cmp(state, _BASE) != is_base_on) {
//         is_base_on = layer_state_cmp(state, _BASE);
//         if (is_base_on) {
//             stop_all_notes();
//         } else {
//             PLAY_SONG(base_sound);
//         }
//     }
// #endif
//     return state;
// }
