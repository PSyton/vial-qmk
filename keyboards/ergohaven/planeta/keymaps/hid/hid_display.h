#include "quantum.h"

typedef enum {
    _DEF = 0,
    _NAV,
    _SYM,
    _ADJ,
    _FOURTH,
    _FIFTH,
    _SIXTH,
    _SEVENTH,
    _EIGHTH,
    _NINTH,
    _TENTH,
    _ELEVENTH,
    _TWELTH,
    _THIRTEENTH,
    _FOURTEENTH,
    _FIFTEENTH,
} layer_number;

typedef enum {
    _TIME = 0xAA, // random value that does not conflict with VIA, must match companion app
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
} hid_data_type;

void display_process_raw_hid_data(uint8_t *data, uint8_t length);
void display_process_layer_state(uint8_t layer);
