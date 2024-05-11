#include "hid.h"
#include <string.h>

static struct hid_data_t hid_data;

struct hid_data_t *get_hid_data(void) {
    return &hid_data;
}

typedef enum {
    _TIME = 0xAA, // random value that does not conflict with VIA, must match companion app
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
} hid_data_type;

void read_string(uint8_t *data, char *string_data) {
    uint8_t data_length = data[1];
    memcpy(string_data, data + 2, data_length);
    string_data[data_length] = '\0';
}

void process_raw_hid_data(uint8_t *data, uint8_t length) {
    uint8_t data_type = data[0];
    switch (data_type) {
        case _TIME:
            hid_data.hours        = data[1];
            hid_data.minutes      = data[2];
            hid_data.time_changed = true;
            break;

        case _VOLUME:
            hid_data.volume_changed = true;
            hid_data.volume         = data[1];
            break;

        case _LAYOUT:
            hid_data.layout         = data[1];
            hid_data.layout_changed = true;
            break;

        case _MEDIA_ARTIST:
            hid_data.media_artist_changed = true;
            read_string(data, hid_data.media_artist);
            break;

        case _MEDIA_TITLE:
            hid_data.media_title_changed = true;
            read_string(data, hid_data.media_title);
            break;
    }
}

/* Active Layer processing */
// layer_state_t layer_state_set_keymap(layer_state_t state) {
//     if (is_display_enabled()) {
//         display_process_layer_state(get_highest_layer(state));
//     }

//     return state;
// }

/* Raw HID processing*/
void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    // if (is_display_enabled()) {
    process_raw_hid_data(data, length);
    // } else if (is_keyboard_master() && !is_display_side()) {
    // dprint("RPC_ID_USER_HID_SYNC \n");
    // transaction_rpc_send(RPC_ID_USER_HID_SYNC, length, data);
    // }
}

// void hid_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
//     if (is_display_enabled()) {
//         display_process_raw_hid_data((uint8_t *)initiator2target_buffer, initiator2target_buffer_size);
//     }
// }

// void keyboard_post_init_user() {
// sync received hid data
// transaction_register_rpc(RPC_ID_USER_HID_SYNC, hid_sync);
// }
