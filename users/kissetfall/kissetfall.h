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

#define APP_A   LSG(KC_A)
#define APP_S   LSG(KC_S)
#define APP_D   LSG(KC_D)
#define APP_F   LSG(KC_F)
#define APP_G   LSG(KC_G)
#define APP_X   LSG(KC_X)
#define APP_C   LSG(KC_C)
#define APP_V   LSG(KC_V)
#define APP_B   LSG(KC_B)


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