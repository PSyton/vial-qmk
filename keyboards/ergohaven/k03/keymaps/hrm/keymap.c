#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "ergohaven_ruen.h"
#include "process_unicode_common.h"
#include "os_detection.h"

enum layer_number {
    _QWERTY = 0,
    _SYMBOLS,
    _NAV
};

static os_variant_t current_os = OS_UNSURE;

// Left-hand home row mods
#define TH_A LT(1,KC_A) // Sybmols layer mod-tap
#define TH_S LALT_T(KC_S)
#define TH_D LSFT_T(KC_D)
#define TH_F LCTL_T(KC_F)
#define TH_G LT(2, KC_G) // Nav layer mod tap
#define TH_Z LGUI_T(KC_Z)

// Right-hand home row mods
#define TH_H LT(2, KC_H) // Nav layer mod tap
#define TH_J RCTL_T(KC_J)
#define TH_K RSFT_T(KC_K)
#define TH_L LALT_T(KC_L)
#define TH_SCLN LT(1,KC_SCLN) // symbols layer mod-tap
#define TH_SLASH RGUI_T(KC_SLASH)

#define TH_M LT(0, KC_M) // tap - 'ь', hold - 'ъ'
#define TH_T LT(0, KC_T) // tap - 'e', hold - 'ё'
#define TH_END LT(0, KC_PGDN)
#define TH_HOME LT(0, KC_PGUP)
#define TH_1 LT(0, KC_1)
#define TH_2 LT(0, KC_2)
#define TH_3 LT(0, KC_3)
#define TH_4 LT(0, KC_4)
#define TH_5 LT(0, KC_5)
#define TH_6 LT(0, KC_6)
#define TH_7 LT(0, KC_7)
#define TH_8 LT(0, KC_8)
#define TH_9 LT(0, KC_9)
#define TH_0 LT(0, KC_0)

#define TH_Q LT(0, KC_Q)
#define TH_W LT(0, KC_W)
#define TH_E LT(0, KC_E)

// Symbols
#define CKC_OABRACE   LG_LT          // '<'
#define CKC_CABRACE   LG_GT          // '>'
#define CKC_AT        LG_AT          // '@'
#define CKC_DOT       LG_DOT         // '.'
#define CKC_GRAVE     LG_GRAVE       // '`'
#define CKC_BACKSLASH KC_BACKSLASH   // '\'
#define CKC_AMPER     LG_AMPR        // '&'
#define CKC_UNDER     LSFT(KC_MINUS) // '_'
#define CKC_OSBRACE   LG_LBR         // '['
#define CKC_CSBRACE   LG_RBR         // ']'
#define CKC_OBRACE    LSFT(KC_9)     // '('
#define CKC_CBRACE    LSFT(KC_0)     // ')'
#define CKC_OFBRACE   LG_LCBR        // '{'
#define CKC_CFBRACE   LG_RCBR        // '}'
#define CKC_PIPE      LG_PIPE        // '|'
#define CKC_TILDA     LG_TILD        // '~'
#define CKC_QUEST     LG_QUES        // '?'
#define CKC_SLASH     LG_SLASH       // '/'
#define CKC_ASTERISK  LSFT(KC_8)     // '*'
#define CKC_PLUS      LSFT(KC_EQUAL) // '+'
#define CKC_MINUS     KC_MINUS       // '-'
#define CKC_EQUAL     KC_EQUAL       // '='
#define CKC_HASH      LG_HASH        // '#'
#define CKC_EXP       LG_CIRC        // '^'
#define CKC_EXCL      LSFT(KC_1)     // '!'
#define CKC_COMA      LG_COMMA       // ','
#define CKC_COLON     LG_COLON       // ':'
#define CKC_SCOLON    LG_SCLN        // ';'
#define CKC_DOLLAR    LG_DLR         // '$'
#define CKC_PERCENT   KC_PERC        // '%'
#define CKC_DQUOTE    LG_DQUO        // '"'
#define CKC_QUOTE     LG_QUOTE       // '''
#define CKC_NUM       LG_NUM         // '№'

enum my_custom_keycodes {
    // Symbols
    U_START = LG_END + 1,
    U_EM_DASH = U_START,     // —
    U_FR_OPEN_QUOTES,        // «
    U_FR_CLOSE_QUOTES,       // »
    U_EN_OPEN_QUOTE,         // ‘
    U_EN_CLOSE_QUOTE,        // ’
    U_EN_DOPEN_QUOTE,        // “
    U_EN_DCLOSE_QUOTE,       // ”
    U_GE_DOPEN_QUOTE,        // „
    U_SIGN_MULTIPLY,         // ×
    U_SIGN_COPYRIGHT,        // ©
    U_SIGN_RIGHTS,           // ®
    U_SIGN_SHTRIC,           // ´
    U_SIGN_TM,               // ™
    U_SIGN_RUBLE,            // ₽
    U_SIGN_EURO,             // €
    U_SIGN_DEGREE,           // °
    U_SIGN_NEQUAL,           // ≠
    U_SIGN_PLUS_MINUS,       // ±
    U_SIGN_3_DOTS,           // …
    U_NB_SPACE,              // 0x00A0 (non breaking space)
    U_END = U_NB_SPACE,
    CKC_STR_UP,              // '../'

    U_ARROW_UP,              // ↑
    U_ARROW_DOWN,            // ↓
    U_ARROW_LEFT,            // ←
    U_ARROW_RIGHT,           // →
    // Universal keys
    KC_OS_CUT = EH_RESERV1,
    KC_OS_COPY = EH_RESERV2,
    KC_OS_PASTE = EH_RESERV3,
    KC_OS_UNDO = LAYER_PREV + 1,
    KC_OS_REDO = LAYER_PREV + 2,
    KC_OS_LOCK = U_ARROW_RIGHT + 1,
};

const char * uni_table[] = {
    "—", // U_EM_DASH
    "«", // U_FR_OPEN_QUOTES
    "»", // U_FR_CLOSE_QUOTES
    "‘", // U_EN_OPEN_QUOTE
    "’", // U_EN_CLOSE_QUOTE
    "“", // U_EN_DOPEN_QUOTE
    "”", // U_EN_DCLOSE_QUOTE
    "„", // U_GE_DOPEN_QUOTE
    "×", // U_SIGN_MULTIPLY
    "©", // U_SIGN_COPYRIGHT
    "®", // U_SIGN_RIGHTS
    "´", // U_SIGN_SHTRIC
    "™", // U_SIGN_TM
    "₽", // U_SIGN_RUBLE
    "€", // U_SIGN_EURO
    "°", // U_SIGN_DEGREE
    "≠", // U_SIGN_NEQUAL
    "±", // U_SIGN_PLUS_MINUS
    "…", // U_SIGN_3_DOTS
    " ", // U_NB_SPACE
    "?", // unused
    "↑", // U_ARROW_UP
    "↓", // U_ARROW_DOWN
    "←", // U_ARROW_LEFT
    "→", // U_ARROW_RIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_QWERTY] = LAYOUT( \
          KC_ESC,              TH_1,    TH_2,    TH_3,    TH_4,   TH_5,                                           TH_6,     TH_7,    TH_8,     TH_9,   TH_0,     KC_BACKSPACE, \
          KC_TAB,              TH_Q,    TH_W,    TH_E,    KC_R,   TH_T,                                           KC_Y,     KC_U,    KC_I,     KC_O,   KC_P,     KC_LEFT_BRACKET, \
          QK_CAPS_WORD_TOGGLE, TH_A,    TH_S,    TH_D,    TH_F,   TH_G,                                           TH_H,     TH_J,    TH_K,     TH_L,   TH_SCLN,  KC_QUOT, \
          LG_SET_EN,           TH_Z,    KC_X,    KC_C,    KC_V,   KC_B,                                           KC_N,     TH_M,    KC_COMM,  KC_DOT, TH_SLASH, LG_SET_RU, \
                                        KC_INS,  KC_PGUP, KC_UP,  KC_LEFT, KC_SPC, KC_HOME,       KC_END, KC_ENT, KC_RIGHT, KC_DOWN, KC_PGDN,  KC_DEL \
        ),

        [_SYMBOLS] = LAYOUT( \
         KC_ESC,           KC_1,         KC_2,      KC_3,         KC_4,      KC_5,                                                   KC_6,      KC_7,       KC_8,        KC_9,        KC_0,          KC_BACKSPACE,
         LG_GRAVE,         KC_BACKSLASH, LG_LT,     LG_GT,        CKC_AT,    CKC_DOT,                                                CKC_AMPER, CKC_UNDER,  CKC_OSBRACE, CKC_CSBRACE, U_SIGN_3_DOTS, U_SIGN_COPYRIGHT,
         U_FR_OPEN_QUOTES, CKC_EXCL,     CKC_MINUS, CKC_PLUS,     CKC_EQUAL, CKC_HASH,                                               CKC_PIPE,  U_EM_DASH,  CKC_OBRACE,  CKC_CBRACE,  CKC_PERCENT,   U_FR_CLOSE_QUOTES,
         U_EN_OPEN_QUOTE,  CKC_QUEST,    CKC_SLASH, CKC_ASTERISK, LG_CIRC,   CKC_COLON,                                              CKC_TILDA, CKC_DOLLAR, CKC_OFBRACE, CKC_CFBRACE, CKC_STR_UP,    U_EN_DCLOSE_QUOTE,
                                         _______,   _______,      _______,   _______,   _______, U_NB_SPACE,       LG_CIRC, _______, _______,   _______,    _______,     _______\
        ),

        [_NAV] = LAYOUT( \
         _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,                                           _______, _______, KC_CIRC, _______, _______,  _______,
         _______, _______, KC_LT,   KC_EQL,  KC_GT,   KC_GRV,                                            _______, KC_LBRC, KC_UNDS, KC_RBRC, _______,  _______,
         _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,                                           KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,  _______,
         _______, _______, KC_ASTR, KC_COLN, KC_SLSH, _______,                                           _______, KC_PIPE, KC_TILD, KC_AMPR, _______,  _______,
                           _______, _______, _______, ADJUST, _______, _______,        _______, _______, _______, _______, _______, _______ \
        ),

      [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, DM_PLY1, DM_REC1,
        _______, _______, _______, _______, _______, _______,                                            _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        _______, _______, _______, _______, _______, CG_TOGG,                                            _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
                          _______, _______, _______, _______, _______, _______,        _______, _______, _______,  _______, _______, _______

       ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
  [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
  [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
  [3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
};
#endif

bool send_unicode_value(const char *str)
{
    uint8_t prev_lang = get_cur_lang();
    if (prev_lang != LANG_EN)
    {
        set_lang(LANG_EN);
    }
    switch (current_os) {
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_MACOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            break;
        default:
            return true;
    };

    send_unicode_string(str);

    if (prev_lang != LANG_EN)
    {
        set_lang(prev_lang);
    }
    return false;
}

void send_string_in_en(const char *string) {
    uint8_t prev_lang = get_cur_lang();
    if (prev_lang != LANG_EN)
    {
        set_lang(LANG_EN);
    }
    SEND_STRING(string);
    if (prev_lang != LANG_EN)
    {
        set_lang(prev_lang);
    }
}

// todo switch language before call
void send_os_specific_keys(uint16_t keycode, bool pressed)
{
    switch (keycode) {
    case KC_OS_CUT:
        switch (current_os) {
            case OS_MACOS:
                if (pressed) send_string_in_en(SS_LGUI("x"));
                break;
            default:
                if (pressed) send_string_in_en(SS_LCTL("x"));
                break;
        };
        break;
    case KC_OS_COPY:
        switch (current_os) {
            case OS_MACOS:
                if (pressed) send_string_in_en(SS_LGUI("c"));
                break;
            default:
                if (pressed) send_string_in_en(SS_LCTL("c"));
                break;
        };
        break;
    case KC_OS_PASTE:
        switch (current_os) {
            case OS_MACOS:
                if (pressed) send_string_in_en(SS_LGUI("v"));
                break;
            default:
                if (pressed) send_string_in_en(SS_LCTL("v"));
                break;
        };
        break;
    case KC_OS_UNDO:
        switch (current_os) {
            case OS_MACOS:
                if (pressed) send_string_in_en(SS_LGUI("y"));
                break;
            default:
                if (pressed) send_string_in_en(SS_LCTL("y"));
                break;
        };
        break;
    case KC_OS_REDO:
        switch (current_os) {
            case OS_MACOS:
                if (pressed) send_string_in_en(SS_LGUI(SS_LSFT("z")));
                break;
            default:
                if (pressed) send_string_in_en(SS_LCTL(SS_LSFT("z")));
                break;
        };
        break;
    case KC_OS_LOCK:
        switch (current_os) {
            case OS_LINUX:
                pressed ? register_code(KC_PWR) : unregister_code(KC_PWR);
                break;
            case OS_MACOS:
                if (pressed) send_string_in_en(SS_LGUI(SS_LCTL("q")));
                break;
            default:
                if (pressed) send_string_in_en(SS_LGUI("l"));
                break;
        };
        break;
    default:
        break;
    };
}

// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(
    uint16_t keycode,
    keyrecord_t* record, uint16_t long_press_keycode, bool only_ru) {
  if (record->tap.count == 0) {  // Key is being held.
      bool long_press_allow = true;
      if (only_ru) {
          long_press_allow = (get_cur_lang() == LANG_RU);
      }
    if (record->event.pressed) {
        if (long_press_allow) {
            tap_code16(long_press_keycode);
        } else {
            tap_code16(QK_MODS_GET_BASIC_KEYCODE(keycode));
        }
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}

static bool process_tap_or_switch_os (
    keyrecord_t* record, os_variant_t os) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      current_os = os;
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}

void handle_language_keys(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t mod_state = get_mods();
        switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
        case KC_1: // en
            if (mod_state & MOD_MASK_CS) {
                set_cur_lang(LANG_EN);
            }
            break;
        case KC_2: // ru
            if (mod_state & MOD_MASK_CS) {
                set_cur_lang(LANG_RU);
            }
            break;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //if (!process_layer_lock(keycode, record, KC_LAYER_LOCK)) {
    //    return false;
    //}
    handle_language_keys(keycode, record);
    if (record->event.pressed) {
        switch (keycode) {
        case U_START ... U_END:
        case U_ARROW_UP ... U_ARROW_RIGHT:
            return send_unicode_value(uni_table[keycode-U_START]);
        case CKC_STR_UP:
            send_string_in_en("../");
            return false;
        };
    }

    switch (keycode) {
        case KC_OS_CUT:
        case KC_OS_COPY:
        case KC_OS_PASTE:
        case KC_OS_UNDO:
        case KC_OS_REDO:
        case KC_OS_LOCK:
            send_os_specific_keys(keycode, record->event.pressed);
            return false;
        case TH_M:
        	return process_tap_or_long_press_key(keycode, record, KC_RBRC, true);
        case TH_T:
        	return process_tap_or_long_press_key(keycode, record, KC_GRV, true);
        case TH_END:
        	return process_tap_or_long_press_key(keycode, record, KC_END, false);
        case TH_HOME:
        	return process_tap_or_long_press_key(keycode, record, KC_HOME, false);
        case TH_1:
        	return process_tap_or_long_press_key(keycode, record, KC_F1, false);
        case TH_2:
        	return process_tap_or_long_press_key(keycode, record, KC_F2, false);
        case TH_3:
        	return process_tap_or_long_press_key(keycode, record, KC_F3, false);
        case TH_4:
        	return process_tap_or_long_press_key(keycode, record, KC_F4, false);
        case TH_5:
        	return process_tap_or_long_press_key(keycode, record, KC_F5, false);
        case TH_6:
        	return process_tap_or_long_press_key(keycode, record, KC_F6, false);
        case TH_7:
        	return process_tap_or_long_press_key(keycode, record, KC_F7, false);
        case TH_8:
        	return process_tap_or_long_press_key(keycode, record, KC_F8, false);
        case TH_9:
        	return process_tap_or_long_press_key(keycode, record, KC_F9, false);
        case TH_0:
        	return process_tap_or_long_press_key(keycode, record, KC_F10, false);
        case TH_Q:
        	return process_tap_or_switch_os(record, OS_WINDOWS);
        case TH_W:
        	return process_tap_or_switch_os(record, OS_LINUX);
        case TH_E:
        	return process_tap_or_switch_os(record, OS_MACOS);
    }

    return true;
}

void keyboard_post_init_user()
{
    set_ruen_toggle_mode(TG_M1M2);
    //debug_enable=true;
}

const char* layer_name_user(int layer) {
    switch (layer) {
        case _QWERTY:
            return "Qwe";
        case _SYMBOLS:
            return "Sym";
        case _NAV:
            return "Nav";
        default:
    }
    return layer_name(layer);
}

const char* layer_upper_name_user(int layer) {
    switch (layer) {
        case _QWERTY:
            return "QWE";
        case _SYMBOLS:
            return "SYM";
        case _NAV:
            return "NAV";
        default:
    }
    return layer_upper_name(layer);
}

const char* get_os_user() {
    switch (current_os) {
        case OS_LINUX: return " L";
        case OS_MACOS: return " M";
        case OS_WINDOWS: return " W";
        default: return " ";
    };
}

void matrix_scan_user(void) {
    if (current_os == OS_UNSURE)
    {
    	current_os = detected_host_os();
    	if (current_os == OS_UNSURE)
    	{
    		current_os = OS_LINUX;
    	}
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_S:
        case TH_D:
        case TH_F:
        case TH_Z:
        case TH_J:
        case TH_K:
        case TH_L:
        case TH_SLASH:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
