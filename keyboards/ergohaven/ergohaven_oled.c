#include "ergohaven.h"
#include "info_config.h"
#include "lang_ru_en.h"
#include "hid.h"
#include "transactions.h"

#ifdef OLED_ENABLE

#    include "bongocat.c"

typedef union {
    uint32_t raw;
    struct {
        uint8_t ruen : 2;
        uint8_t oled_slave : 3;
        uint8_t oled_master : 3;
        bool    right_encoder : 1;
        bool    left_encoder : 1;
    };
} vial_config_t;

vial_config_t vial_config;

typedef enum {
    OLED_STATUS = 0,
    OLED_STATUS_CLASSIC,
    OLED_MEDIA,
    OLED_SPLASH,
    OLED_BONGOCAT,
    OLED_DISABLED,
} oled_mode_t;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        if (vial_config.oled_master == OLED_BONGOCAT) return is_keyboard_left() ? OLED_ROTATION_0 : OLED_ROTATION_180;
        if (vial_config.oled_master == OLED_MEDIA) return is_keyboard_left() ? OLED_ROTATION_0 : OLED_ROTATION_180;
    } else {
        if (vial_config.oled_slave == OLED_BONGOCAT) return is_keyboard_left() ? OLED_ROTATION_0 : OLED_ROTATION_180;
        if (vial_config.oled_slave == OLED_MEDIA) return is_keyboard_left() ? OLED_ROTATION_0 : OLED_ROTATION_180;
    }
    return OLED_ROTATION_270;
}

void render_status(void) {
    // Print current mode
    if (strlen(PRODUCT) <= 5)
        oled_write_ln_P(PSTR(PRODUCT), false);
    else // Imperial44 is too long name
        oled_write_ln_P(PSTR("\n"), false);

    oled_write_ln_P(PSTR("v3.3\n"), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_ln_P("MODE:", false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("Mac"), false);
    } else {
        oled_write_ln_P(PSTR("Win"), false);
    }

    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    oled_write_ln_P(PSTR(layer_name(get_highest_layer(layer_state))), false);

    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

void render_status2(void) {
    oled_write_ln(layer_upper_name(get_highest_layer(layer_state)), false);
    oled_set_cursor(0, 1);
    if (keymap_config.swap_lctl_lgui)
        oled_write_P(PSTR("   \01\02   \03\04"), false);
    else
        oled_write_P(PSTR("          "), false);

    oled_set_cursor(0, 2);
    oled_write(get_cur_lang() == LANG_EN ? "EN" : "RU", false);

    oled_set_cursor(0, 4);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.caps_lock ? PSTR("CPS\07\10") : PSTR("CPS\05\06"), false);
    oled_write_P(led_usb_state.num_lock ? PSTR("NUM\07\10") : PSTR("NUM\05\06"), false);

    oled_set_cursor(0, 7);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT ? PSTR("SFT\07\10") : PSTR("SFT\05\06"), false);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL ? PSTR("CTL\07\10") : PSTR("CTL\05\06"), false);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT ? PSTR("ALT\07\10") : PSTR("ALT\05\06"), false);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI ? PSTR("GUI\07\10") : PSTR("GUI\05\06"), false);

    char buf[16];
    int  wpm = get_current_wpm();
    if (wpm < 10)
        sprintf(buf, "WPM %d", wpm);
    else if (wpm < 100)
        sprintf(buf, "W  %d", wpm);
    else
        sprintf(buf, "W %d", wpm);
    oled_set_cursor(0, 12);
    oled_write_ln(buf, false);

    struct hid_data_t* hid_data = get_hid_data();
    if (hid_data->time_changed) {
        sprintf(buf, "%02d:%02d", hid_data->hours, hid_data->minutes);
        oled_set_cursor(0, 14);
        oled_write_ln(buf, false);
    }
}

void render_media(void) {
    struct hid_data_t* hid_data = get_hid_data();
    if (hid_data->media_artist_changed || hid_data->media_title_changed) {
        oled_set_cursor(0, 1);
        hid_data->media_title[21] = '\0';
        oled_write_ln(hid_data->media_title, false);
        oled_set_cursor(0, 3);
        hid_data->media_artist[21] = '\0';
        oled_write_ln(hid_data->media_artist, false);
    }
}

__attribute__((weak)) void ergohaven_dark_draw(void) {}

void via_set_layout_options_kb(uint32_t value) {
    vial_config_t new_via_layouts;
    new_via_layouts.raw = value;
    if (is_keyboard_master()) {
        if (vial_config.oled_master != new_via_layouts.oled_master) {
            vial_config = new_via_layouts;
            oled_init(OLED_ROTATION_0);
        }
    } else {
        if (vial_config.oled_slave != new_via_layouts.oled_slave) {
            vial_config = new_via_layouts;
            oled_init(OLED_ROTATION_0);
        }
    }
    vial_config = new_via_layouts;
}

bool oled_task_kb(void) {
    // Defer to the keymap if they want to override
    if (!oled_task_user()) {
        return false;
    }

    uint8_t mode = is_keyboard_master() ? vial_config.oled_master : vial_config.oled_slave;
    switch (mode) {
        case OLED_STATUS_CLASSIC:
            render_status();
            break;

        case OLED_STATUS:
            render_status2();
            break;
        case OLED_MEDIA:
            render_media();
            break;

        case OLED_SPLASH:
            ergohaven_dark_draw();
            break;

        case OLED_BONGOCAT:
            render_bongocat();
            break;

        case OLED_DISABLED:
        default:
            break;
    }

    return false;
}

void sync_config(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    uint32_t value;
    memcpy(&value, in_data, sizeof(uint32_t));
    via_set_layout_options_kb(value);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(RPC_SYNC_CONFIG, sync_config);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            if (transaction_rpc_send(RPC_SYNC_CONFIG, sizeof(vial_config_t), &vial_config)) {
                last_sync = timer_read32();
            }
        }
    }
}

void housekeeping_task_kb(void) {
    struct hid_data_t* hid_data = get_hid_data();
    if (hid_data->layout_changed) {
        bool synced              = lang_sync_external(hid_data->layout);
        hid_data->layout_changed = !synced;
    }
    housekeeping_task_user();
}

#endif
