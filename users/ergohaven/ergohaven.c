#include "ergohaven.h"

#ifdef AUDIO_ENABLE
float base_sound[][2] = SONG(TERMINAL_SOUND);
float caps_sound[][2] = SONG(CAPS_LOCK_ON_SOUND);
#endif

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;    

// custom keycodes
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef WPM_ENABLE
    if (record->event.pressed) {
        extern uint32_t tap_timer;
        tap_timer = timer_read32();
    }
  #endif

  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    case NEXTSEN:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING(". ");
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif 
        add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
      }
      return false;

    case PREDL:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING("/ ");
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif
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
    #ifdef OLED_GAMING
        case GM_INV:
            // Toggle gaming mode & clear OLED display
            if (!record->event.pressed) {
                toggleGamingMode();
                if (isGamingMode()) {
                    readMainTimer();
                    initGame();
                    startGame();
                }
                oled_clear();
            }
            break;
        case KC_S:
            if (record->event.pressed) {
                if (isGamingMode()) {
                    movePlayer(1); // 1 = isLeft
                    return false;
                }
            }
            break;
        case KC_F:
            if (record->event.pressed) {
                if (isGamingMode()) {
                    movePlayer(0); // 0 = isRight
                    return false;
                }
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                if (isGamingMode()) {
                    firePlayerBeam();
                    return false;
                }
            }
            break;
        case KC_ENT:
        case KC_LGUI:
            if (record->event.pressed) {
                if (isGamingMode()) {
                    return false;
                }
            }
            break;
    #endif

    case KC_CAPS:
      if (record->event.pressed) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif 
        }      
      return true; // Let QMK send the enter press/release events
                  
    case LAYER_NEXT:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

      uint8_t current_layer = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
      return false;

    case LAYER_PREV:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

      uint8_t this_layer  = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (this_layer > LAYER_CYCLE_END || this_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t prev_layer = this_layer - 1;
      if (prev_layer > LAYER_CYCLE_END) {
          prev_layer = LAYER_CYCLE_START;
      }
      layer_move(prev_layer);
      return false;
    default:
      return true; // Process all other keycodes normally
  }
   return process_record_keymap(keycode, record);
}



void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  #ifdef OLED_GAMING
    if (isGamingMode()) {
        if (countMainTimer() > 0) {
            game_main();
        }
    }
  #endif
}



__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user (layer_state_t state) {
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
  return layer_state_set_keymap (state);
}