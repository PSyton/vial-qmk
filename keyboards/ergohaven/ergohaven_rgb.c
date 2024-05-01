#include "quantum.h"
#include "ergohaven.h"

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM my_base_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CYAN});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GOLDENROD});

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_base_layer, my_layer1_layer, my_layer2_layer, my_layer3_layer);
#endif

void keyboard_post_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_layers = my_rgb_layers;
#endif
    keyboard_post_init_user();
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
#endif
    return default_layer_state_set_user(state);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
#endif
    return layer_state_set_user(state);
}
