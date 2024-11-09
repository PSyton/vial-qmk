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

#define HR_1 LT(0, KC_1)
#define HR_2 LT(0, KC_2)
#define HR_3 LT(0, KC_3)
#define HR_4 LT(0, KC_4)
#define HR_5 LT(0, KC_5)
#define HR_6 LT(0, KC_6)
#define HR_7 LT(0, KC_7)
#define HR_8 LT(0, KC_8)
#define HR_9 LT(0, KC_9)
#define HR_0 LT(0, KC_0)

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
    U_ARROW_UP,              // ↑
    U_ARROW_DOWN,            // ↓
    U_ARROW_LEFT,            // ←
    U_ARROW_RIGHT,           // →
    U_END = U_ARROW_RIGHT,
    KC_2_DOTS,               // '..'
    KC_ARROW,                // '->'
    KC_4_DOTS,               // '::'
    // Universal keys
    KC_OS_CUT,
    KC_OS_COPY,
    KC_OS_PASTE,
    KC_OS_UNDO,
    KC_OS_REDO,
    KC_OS_LOCK,
    // force set os key
    KC_OS_UNX,
    KC_OS_WIN,
    KC_OS_MAC,
    SMTD_KEYCODES_BEGIN,
    HR_A,
    HR_S,
    HR_D,
    HR_F,
    HR_G,
    HR_H,
    HR_J,
    HR_K,
    HR_L,
    HR_SCLN,
    SMTD_KEYCODES_END,
};

#include "sm_td.h"

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
    "↑", // U_ARROW_UP
    "↓", // U_ARROW_DOWN
    "←", // U_ARROW_LEFT
    "→", // U_ARROW_RIGHT
};

const uint16_t mac_keycodes[] = {
    G(KC_X),    // KC_OS_CUT
    G(KC_C),    // KC_OS_COPY
    G(KC_V),    // KC_OS_PASTE
    G(KC_Z),    // KC_OS_UNDO
    G(KC_Y),    // KC_OS_REDO
    G(C(KC_Q)), // KC_OS_LOCK
    G(KC_LEFT), // KC_HOME
    G(KC_RGHT), // KC_END
};

const uint16_t win_keycodes[] = {
    C(KC_X),    // KC_OS_CUT
    C(KC_C),    // KC_OS_COPY
    C(KC_V),    // KC_OS_PASTE
    C(KC_Z),    // KC_OS_UNDO
    C(KC_Y),    // KC_OS_REDO
    G(KC_L),    // KC_OS_LOCK
    KC_HOME,    // KC_HOME
    KC_END,     // KC_END
};

const uint16_t lin_keycodes[] = {
    C(KC_X),    // KC_OS_CUT
    C(KC_C),    // KC_OS_COPY
    C(KC_V),    // KC_OS_PASTE
    C(KC_Z),    // KC_OS_UNDO
    C(KC_Y),    // KC_OS_REDO
    KC_PWR,     // KC_OS_LOCK
    KC_HOME,    // KC_HOME
    KC_END,     // KC_END
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_QWERTY] = LAYOUT( \
          KC_ESC,              HR_1,    HR_2,    HR_3,    HR_4,   HR_5,                                              HR_6,     HR_7,    HR_8,     HR_9,   HR_0,     KC_BACKSPACE, \
          KC_TAB,              KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                                              KC_Y,     KC_U,    KC_I,     KC_O,   KC_P,     KC_LEFT_BRACKET, \
          QK_CAPS_WORD_TOGGLE, HR_A,    HR_S,    HR_D,    HR_F,   HR_G,                                              HR_H,     HR_J,    HR_K,     HR_L,   HR_SCLN,  KC_QUOT, \
          LG_SET_EN,           KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                                              KC_N,     KC_M,    KC_COMM,  KC_DOT, KC_SLASH, LG_SET_RU, \
                                        KC_INS,  KC_PGUP, KC_UP,  KC_LEFT, KC_SPC, TG(_NAV),       MO(_NAV), KC_ENT, KC_RIGHT, KC_DOWN, KC_PGDN,  KC_DEL \
        ),

        [_SYMBOLS] = LAYOUT( \
         KC_ESC,           U_SIGN_RIGHTS,      LG_NUM,    U_SIGN_3_DOTS, LG_COLON,  LG_SCLN,                                                    LG_GRAVE,  U_SIGN_SHTRIC, CKC_OBRACE,  CKC_CBRACE,  U_EN_OPEN_QUOTE,  U_EN_CLOSE_QUOTE,
         U_EN_DOPEN_QUOTE, U_EN_DCLOSE_QUOTE,  LG_LT,     LG_GT,         CKC_AT,    CKC_TILDA,                                                  CKC_AMPER, CKC_UNDER,     CKC_OSBRACE, CKC_CSBRACE, U_FR_OPEN_QUOTES, U_FR_CLOSE_QUOTES,
         U_GE_DOPEN_QUOTE, CKC_EXCL,           CKC_MINUS, CKC_PLUS,      CKC_EQUAL, CKC_HASH,                                                   LG_DLR,    U_EM_DASH,     LG_LCBR,     LG_RCBR,     U_SIGN_DEGREE,    U_SIGN_RUBLE,
         U_SIGN_COPYRIGHT, CKC_QUEST,          CKC_SLASH, CKC_ASTERISK,  LG_CIRC,   CKC_PERCENT,                                                KC_ARROW,  KC_4_DOTS,     LG_COMMA,    LG_DOT,      LG_PIPE,          U_SIGN_EURO,
                                               KC_GRAVE,  KC_RCBR,       XXXXXXX,   XXXXXXX,     XXXXXXX, U_NB_SPACE,       KC_2_DOTS, XXXXXXX, XXXXXXX,   XXXXXXX,       XXXXXXX,     XXXXXXX\
        ),

        [_NAV] = LAYOUT( \
         KC_ESC,     KC_F1,      KC_F2,     KC_F3,      KC_F4,       KC_F5,                                                 KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_F10,  KC_BACKSPACE,
         XXXXXXX,    KC_MPRV,    KC_VOLD,   KC_VOLU,    KC_MPLY,     KC_MNXT,                                               KC_TAB,  KC_HOME, KC_UP,   KC_END,    KC_F11,  XXXXXXX,
         XXXXXXX,    XXXXXXX,    KC_LALT,   KC_LSFT,    KC_LCTL,     KC_LEFT_GUI,                                           KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT,  KC_F12,  XXXXXXX,
         KC_OS_LOCK, KC_OS_REDO, KC_OS_CUT, KC_OS_COPY, KC_OS_PASTE, KC_OS_REDO,                                            KC_INS,  KC_PGUP, XXXXXXX, KC_PGDN,   XXXXXXX, KC_PRINT_SCREEN,
                                 XXXXXXX,   XXXXXXX,    XXXXXXX,     XXXXXXX,     KC_SPC, TG(_NAV),        XXXXXXX, KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
        ),

      [_ADJUST] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, DM_PLY1, DM_REC1,
        _______, _______, _______, _______, _______, _______,                                            _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        _______, _______, _______, _______, _______, _______,                                            _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
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

// TODO Switch language?
bool send_os_specific_keys(uint16_t keycode, bool pressed)
{
    uint16_t target_keycode = keycode;
    switch (current_os) {
        case OS_LINUX:
            if (keycode == KC_HOME) {
                target_keycode = lin_keycodes[6];
            } else if (keycode == KC_END) {
                target_keycode = lin_keycodes[7];
            } else {
                target_keycode = lin_keycodes[keycode-KC_OS_CUT];
            }
            break;
        case OS_MACOS:
            if (keycode == KC_HOME) {
                target_keycode = mac_keycodes[6];
            } else if (keycode == KC_END) {
                target_keycode = mac_keycodes[7];
            } else {
                target_keycode = mac_keycodes[keycode-KC_OS_CUT];
            }
            break;
        case OS_WINDOWS:
            if (keycode == KC_HOME) {
                target_keycode = win_keycodes[6];
            } else if (keycode == KC_END) {
                target_keycode = win_keycodes[7];
            } else {
                target_keycode = win_keycodes[keycode-KC_OS_CUT];
            }
            break;
        default:
            break;
    };
    if (target_keycode == keycode) {
        return true;
    }
    if (pressed) {
        register_code16(target_keycode);
    } else {
        unregister_code16(target_keycode);
    }
    return false;
}

// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(
    uint16_t keycode,
    keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
        tap_code16(long_press_keycode);
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
    if (!process_smtd(keycode, record)) {
        return false;
    }
    handle_language_keys(keycode, record);
    if (record->event.pressed) {
        switch (keycode) {
        case U_START ... U_END:
            return send_unicode_value(uni_table[keycode-U_START]);
        case KC_2_DOTS:
            send_string_in_en("..");
            return false;
        case KC_ARROW:                // '->'
            send_string_in_en("->");
            return false;
        case KC_4_DOTS:               // '::'
            send_string_in_en("::");
            return false;
        };
    }

    switch (keycode) {
        case KC_OS_CUT ... KC_OS_LOCK:
        case KC_HOME:
        case KC_END:
            return send_os_specific_keys(keycode, record->event.pressed);
        case HR_1:
        	return process_tap_or_long_press_key(keycode, record, KC_F1);
        case HR_2:
        	return process_tap_or_long_press_key(keycode, record, KC_F2);
        case HR_3:
        	return process_tap_or_long_press_key(keycode, record, KC_F3);
        case HR_4:
        	return process_tap_or_long_press_key(keycode, record, KC_F4);
        case HR_5:
        	return process_tap_or_long_press_key(keycode, record, KC_F5);
        case HR_6:
        	return process_tap_or_long_press_key(keycode, record, KC_F6);
        case HR_7:
        	return process_tap_or_long_press_key(keycode, record, KC_F7);
        case HR_8:
        	return process_tap_or_long_press_key(keycode, record, KC_F8);
        case HR_9:
        	return process_tap_or_long_press_key(keycode, record, KC_F9);
        case HR_0:
        	return process_tap_or_long_press_key(keycode, record, KC_F10);
        case KC_OS_WIN:
        	current_os = OS_WINDOWS;
            return false;
        case KC_OS_UNX:
        	current_os = OS_LINUX;
            return false;
        case KC_OS_MAC:
        	current_os = OS_MACOS;
            return false;
        case KC_SLASH:
            {
                static bool bs_registered = false;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code(KC_BSLS);
                        bs_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // on release KC_SLASH
                    if (bs_registered) {
                        unregister_code(KC_BSLS);
                        bs_registered = false;
                        return false;;
                    }
                }
            }
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

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_LT(HR_A, KC_A, 1)
        SMTD_MT(HR_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(HR_D, KC_D, KC_LSFT)
        SMTD_MT(HR_F, KC_F, KC_LEFT_CTRL)
        SMTD_MT(HR_G, KC_G, KC_LEFT_GUI)
        SMTD_MT(HR_H, KC_H, KC_RIGHT_GUI)
        SMTD_MT(HR_J, KC_J, KC_RIGHT_CTRL)
        SMTD_MT(HR_K, KC_K, KC_RSFT)
        SMTD_MT(HR_L, KC_L, KC_LEFT_ALT)
        SMTD_LT(HR_SCLN, KC_SCLN, 1)
    }
}
