#pragma once

#include "quantum.h"

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
#define CTRLUP  LCTL(KC_LEFT)
#define CTRLDN  LCTL(KC_RIGHT)
#define LANG    LALT(KC_LSFT)

#define APP_A   LSG(KC_A)
#define APP_S   LSG(KC_S)
#define APP_D   LSG(KC_D)
#define APP_F   LSG(KC_F)
#define APP_G   LSG(KC_G)
#define APP_X   LSG(KC_X)
#define APP_C   LSG(KC_C)
#define APP_V   LSG(KC_V)
#define APP_B   LSG(KC_B)

#define SLV_H   KC_H
#define SLV_I   KC_I
#define SLV_L   KC_L
#define SLV_M   KC_M
#define SLV_N   KC_N
#define SLV_O   KC_O
#define SLV_P   KC_P
#define SLV_Y   KC_Y
#define SLV_SX  LSFT(KC_X)
#define SLV_SW  LSFT(KC_W)

enum custom_keycodes {
    NEXTSEN = QK_KB,
    PREDL, 
    BRACES,
    PARENTH,
    ALT_TAB,
};
