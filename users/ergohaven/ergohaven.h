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

#define BASE      DF(_BASE)
#define RAISE     MO(_RAISE)
#define LOWER     MO(_LOWER)
#define ADJUST    MO(_ADJUST)
#define PREVWRD   LCTL(KC_LEFT)
#define NEXTWRD   LCTL(KC_RIGHT)
#define CT_Q  LCTL_T(KC_Q)
#define CT_CM RCTL_T(KC_COMM)
#define SF_Z  LSFT_T(KC_Z)
#define SF_SS RSFT_T(KC_SLSH)
#define AL_X  LALT_T(KC_X)
#define AL_DT RALT_T(KC_DOT)
#define LO_TB LT(LOWER, KC_TAB)

enum custom_keycodes {
    NEXTSEN = QK_KB,
    PREDL, 
    BRACES,
    PARENTH,
    ALT_TAB,
    LAYER_NEXT,
    LAYER_PREV,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   15
