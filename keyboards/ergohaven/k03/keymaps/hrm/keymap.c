#include QMK_KEYBOARD_H
#include "ergohaven.h"
#include "ergohaven_ruen.h"
#include "process_unicode_common.h"
#include "os_detection.h"
#include "features/achordion.h"
#include "features/layer_lock.h"

enum layer_number {
    _QWERTY = 0,
    _SYMBOLS,
    _NAV
};

static os_variant_t current_os = OS_UNSURE;

#define HR_1 LT(0, KC_F1)
#define HR_2 LT(0, KC_F2)
#define HR_3 LT(0, KC_F3)
#define HR_4 LT(0, KC_F4)
#define HR_5 LT(0, KC_F5)
#define HR_6 LT(0, KC_F6)
#define HR_7 LT(0, KC_F7)
#define HR_8 LT(0, KC_F8)
#define HR_9 LT(0, KC_F9)
#define HR_10 LT(0, KC_F10)
#define HR_11 LT(0, KC_F11)
#define HR_12 LT(0, KC_F12)

// home row mods
#define HR_A LT(1, KC_A)
#define HR_S ALT_T(KC_S)
#define HR_D SFT_T(KC_D)
#define HR_F CTL_T(KC_F)
#define HR_G CMD_T(KC_G)
#define HR_H CMD_T(KC_H)
#define HR_J CTL_T(KC_J)
#define HR_K SFT_T(KC_K)
#define HR_L ALT_T(KC_L)
#define HR_SCLN LT(1, KC_SCLN)

#define TH_ENTER LT(2, KC_ENT)

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
    KC_W_BEGIN,
    KC_W_END,
    // force set os key
    KC_OS_UNX,
    KC_OS_WIN,
    KC_OS_MAC,
    KC_LLOCK,
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
    "↑", // U_ARROW_UP
    "↓", // U_ARROW_DOWN
    "←", // U_ARROW_LEFT
    "→", // U_ARROW_RIGHT
};

const uint16_t mac_keycodes[] = {
    G(KC_X),        // KC_OS_CUT
    G(KC_C),        // KC_OS_COPY
    G(KC_V),        // KC_OS_PASTE
    G(KC_Z),        // KC_OS_UNDO
    G(KC_Y),        // KC_OS_REDO
    G(C(KC_Q)),     // KC_OS_LOCK
    G(C(KC_LEFT)),  // KC_W_BEGIN
    G(C(KC_RIGHT)), // KC_OS_END
    G(KC_LEFT),     // KC_HOME
    G(KC_RGHT),     // KC_END
};

const uint16_t win_keycodes[] = {
    C(KC_X),     // KC_OS_CUT
    C(KC_C),     // KC_OS_COPY
    C(KC_V),     // KC_OS_PASTE
    C(KC_Z),     // KC_OS_UNDO
    C(KC_Y),     // KC_OS_REDO
    G(KC_L),     // KC_OS_LOCK
    C(KC_LEFT),  // KC_W_BEGIN
    C(KC_RIGHT), // KC_OS_END
    KC_HOME,     // KC_HOME
    KC_END,      // KC_END
};

const uint16_t lin_keycodes[] = {
    C(KC_X),     // KC_OS_CUT
    C(KC_C),     // KC_OS_COPY
    C(KC_V),     // KC_OS_PASTE
    C(KC_Z),     // KC_OS_UNDO
    C(KC_Y),     // KC_OS_REDO
    KC_PWR,      // KC_OS_LOCK
    C(KC_LEFT),  // KC_W_BEGIN
    C(KC_RIGHT), // KC_OS_END
    KC_HOME,     // KC_HOME
    KC_END,      // KC_END
};

const uint16_t long_tap_actions[] = {
    KC_1,
    KC_2,
    KC_3,
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_0,
    KC_MINUS,
    LSFT(KC_EQUAL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_QWERTY] = LAYOUT( \
          KC_ESC,       KC_1,     KC_2,    KC_3,    KC_4,   KC_5,                                            KC_6,   KC_7,     KC_8,     KC_9,   KC_0,     QK_CAPS_WORD_TOGGLE,\
          KC_TAB,       KC_Q,     KC_W,    KC_E,    KC_R,   KC_T,                                            KC_Y,   KC_U,     KC_I,     KC_O,   KC_P,     KC_LEFT_BRACKET, \
          LSFT(KC_TAB), HR_A,     HR_S,    HR_D,    HR_F,   HR_G,                                            HR_H,   HR_J,     HR_K,     HR_L,   HR_SCLN,  KC_QUOT, \
          LG_SET_EN,    KC_Z,     KC_X,    KC_C,    KC_V,   KC_B,                                            KC_N,   KC_M,     KC_COMM,  KC_DOT, KC_SLASH, LG_SET_RU, \
                        LG_RU_YO, KC_UP,  KC_LEFT,  KC_BACKSPACE, KC_SPC, MO(_NAV),        MO(_NAV), KC_ENT, KC_DEL, KC_RIGHT, KC_DOWN, LG_RU_HRD_SGN \
        ),

        [_SYMBOLS] = LAYOUT( \
         KC_ESC,           U_SIGN_RIGHTS,      LG_NUM,    U_SIGN_3_DOTS, LG_COLON,  LG_SCLN,                                                                     LG_GRAVE,   U_SIGN_SHTRIC, U_SIGN_DEGREE,  KC_2_DOTS,   U_EN_OPEN_QUOTE,  U_EN_CLOSE_QUOTE,
         U_EN_DOPEN_QUOTE, U_EN_DCLOSE_QUOTE,  LG_LT,     LG_GT,         CKC_AT,    CKC_TILDA,                                                                   CKC_AMPER,  CKC_UNDER,     CKC_OSBRACE,    CKC_CSBRACE, KC_ARROW,         XXXXXXX,
         U_GE_DOPEN_QUOTE, CKC_EXCL,           CKC_MINUS, CKC_PLUS,      CKC_EQUAL, CKC_HASH,                                                                    CKC_OBRACE, CKC_CBRACE,    LG_LCBR,        LG_RCBR,     LG_DLR,           U_SIGN_RUBLE,
         U_SIGN_COPYRIGHT, CKC_QUEST,          CKC_SLASH, CKC_ASTERISK,  LG_CIRC,   CKC_PERCENT,                                                                 KC_4_DOTS,  U_EM_DASH,     LG_COMMA,       LG_DOT,      LG_PIPE,          U_SIGN_EURO,
                                               XXXXXXX,   XXXXXXX,       XXXXXXX,   XXXXXXX,     U_NB_SPACE, U_FR_OPEN_QUOTES,       U_FR_CLOSE_QUOTES, XXXXXXX, XXXXXXX,    XXXXXXX,       XXXXXXX,        XXXXXXX \
        ),

        [_NAV] = LAYOUT( \
         KC_F1,        KC_F2,      KC_F3,      KC_F4,      KC_F5,       KC_F6,                                                KC_F7,           KC_F8,       KC_F9,   KC_F10,    KC_F11,   KC_F12,
         KC_TAB,       KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MPLY,     KC_MNXT,                                              KC_PGUP,         KC_HOME,     KC_UP,   KC_END,    KC_PGUP,  XXXXXXX,
         LSFT(KC_TAB), XXXXXXX,    KC_LALT,    KC_LSFT,    KC_LCTL,     KC_LEFT_GUI,                                          KC_PGDN,         KC_LEFT,     KC_DOWN, KC_RIGHT,  KC_PGDN,  XXXXXXX,
         XXXXXXX,      KC_OS_REDO, KC_OS_CUT,  KC_OS_COPY, KC_OS_PASTE, KC_OS_REDO,                                           KC_PRINT_SCREEN, KC_W_BEGIN,  XXXXXXX, KC_W_END,  XXXXXXX,  OSL(3),
                                   KC_OS_LOCK, XXXXXXX,    XXXXXXX,     KC_BACKSPACE, KC_SPC, KC_LLOCK,     KC_LLOCK, KC_ENT, KC_DEL,          XXXXXXX,     XXXXXXX, XXXXXXX \
        ),

      [_ADJUST] = LAYOUT(
        QK_BOOT, _______,   _______,   _______,   _______, _______,                                            _______, _______, _______, _______, _______, _______,
        _______, KC_OS_UNX, KC_OS_WIN, KC_OS_MAC, _______, _______,                                            _______, _______, _______, _______, DM_PLY1, DM_REC1,
        _______, _______,   _______,   _______,   _______, _______,                                            _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        _______, _______,   _______,   _______,   _______, _______,                                            _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
                            _______,   _______,   _______, _______, _______, _______,        _______, _______, _______,  _______, _______, _______

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
    int index = keycode-KC_OS_CUT;
    switch (keycode) {
        case KC_HOME:
        index = 8;
        break;
        case KC_END:
        index = 9;
        break;
        default:
        break;
    }

    switch (current_os) {
        case OS_LINUX:
            target_keycode = lin_keycodes[index];
            break;
        case OS_MACOS:
            target_keycode = mac_keycodes[index];
            break;
        case OS_WINDOWS:
            target_keycode = win_keycodes[index];
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
static bool process_tap_or_long_press_key(uint16_t keycode, keyrecord_t* record) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
        tap_code16(long_tap_actions[keycode-HR_1]);
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
    if (!process_achordion(keycode, record)) { return false; }
    if (!process_layer_lock(keycode, record, KC_LLOCK)) { return false; }

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
        case KC_OS_CUT ... KC_W_END:
        case KC_HOME:
        case KC_END:
            return send_os_specific_keys(keycode, record->event.pressed);
        case HR_1 ... HR_12:
       	    return process_tap_or_long_press_key(keycode, record);
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
    achordion_task();
    if (current_os == OS_UNSURE)
    {
    	current_os = detected_host_os();
    	if (current_os == OS_UNSURE)
    	{
    		current_os = OS_LINUX;
    	}
    }
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // todo
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_ENTER:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
