#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "hid_display.h"
#include "raw_hid.h"

// #ifdef AUDIO_ENABLE
// float base_sound[][2] = SONG(TERMINAL_SOUND);
// float caps_sound[][2] = SONG(CAPS_LOCK_ON_SOUND);
// #endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_BASE] = LAYOUT( \
         KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,                               KC_6,    KC_7,  KC_8,     KC_9,    KC_0,    KC_BSPC, \
         KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,                               KC_Y,    KC_U,  KC_I,     KC_O,    KC_P,    KC_BSLS, \
         KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                               KC_H,    KC_J,  KC_K,     KC_L,    KC_SCLN, KC_QUOT, \
         KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,                               KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT, \
                  KC_LGUI, KC_LALT, KC_LCTL, LOWER, KC_SPC, KC_LBRC,           KC_RBRC, KC_ENT,  RAISE, KC_RCTL,  KC_RALT, KC_RGUI \
        ),

        [_LOWER] = LAYOUT( \
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,                           KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,
         _______, _______, KC_HOME, KC_UP,   KC_END,   KC_INS,                          KC_PGUP, KC_7,   KC_8,    KC_9,    _______, _______,
         _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT,                          KC_PGDN, KC_4,   KC_5,    KC_6,    KC_0,    _______,
         _______, _______, PREVWRD, KC_CAPS, NEXTWRD,  KC_DEL,                          KC_PSCR, KC_1,   KC_2,    KC_3,    _______, _______,
                  _______, _______, _______, _______, _______, _______,        _______, _______, ADJUST, _______, _______, _______\
        ),

        [_RAISE] = LAYOUT( \
         _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,                          _______, _______, KC_CIRC, _______, _______,  _______,
         _______, _______, KC_LT,   KC_EQL,  KC_GT,   KC_GRV,                           _______, KC_LBRC, KC_UNDS, KC_RBRC, _______,  _______,
         _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                          KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,  _______,
         _______, _______, KC_ASTR, KC_COLN, KC_SLSH, _______,                          _______, KC_PIPE, KC_TILD, KC_AMPR, _______,  _______,
                  _______, _______, _______, ADJUST,  _______,  _______,        _______, _______, _______, _______, _______, _______ \
        ),
    
      [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                           CG_TOGG, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, DM_PLY1, DM_REC1,
        _______, CK_RST,  CK_DOWN, CK_UP,   CK_TOGG, AU_TOGG,                           _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        _______, _______, _______, _______, _______, _______,                           _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
                 _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______                  
       ),
};



/* Active Layer processing */
// layer_state_t layer_state_set_keymap(layer_state_t state) {
//     if (is_display_enabled()) {
//         display_process_layer_state(get_highest_layer(state));
//     }

//     return state;
// }

/* Raw HID processing*/
void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    dprintf("raw_hid_receive - received %u bytes \n", length);

    // if (is_display_enabled()) {
        display_process_raw_hid_data(data, length);
    // } else if (is_keyboard_master() && !is_display_side()) {
        // dprint("RPC_ID_USER_HID_SYNC \n");
        // transaction_rpc_send(RPC_ID_USER_HID_SYNC, length, data);
    // }
}

void hid_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (is_display_enabled()) {
        display_process_raw_hid_data((uint8_t *)initiator2target_buffer, initiator2target_buffer_size);
    }
}

// void keyboard_post_init_user() {
    // sync received hid data
    // transaction_register_rpc(RPC_ID_USER_HID_SYNC, hid_sync);
// }
#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED}
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_GOLDENROD}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,    
    my_layer1_layer,    
    my_layer2_layer,    
    my_layer3_layer     
);


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));

    if (is_display_enabled()) {
        display_process_layer_state(get_highest_layer(state));
    }
    //   #if defined(AUDIO_ENABLE)
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
    return state;

}
#endif
