#include "display.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include "lang_ru_en.h"

#define MODS_SHIFT ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
#define MODS_CTRL ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL)
#define MODS_ALT ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT)
#define MODS_GUI ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI)

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

static uint16_t home_screen_timer = 0;

static bool display_enabled;

/* shared styles */
lv_style_t style_screen;
lv_style_t style_container;
lv_style_t style_button;
lv_style_t style_button_active;

/* screens */
static lv_obj_t *screen_home;
static lv_obj_t *screen_volume;
static lv_obj_t *screen_media;

/* home screen content */
static lv_obj_t *label_time;
static lv_obj_t *label_volume_home;
static lv_obj_t *label_shift;
static lv_obj_t *label_ctrl;
static lv_obj_t *label_alt;
static lv_obj_t *label_gui;
static lv_obj_t *label_layer;
static lv_obj_t *label_caps;
static lv_obj_t *label_layout;

/* volume screen content */
static lv_obj_t *arc_volume;
static lv_obj_t *label_volume_arc;

/* media screen content */
static lv_obj_t *label_media_artist;
static lv_obj_t *label_media_title;

/* public function to be used in keymaps */
bool is_display_enabled(void) {
    return display_enabled;
}

void init_styles(void) {
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_black());

    lv_style_init(&style_container);
    lv_style_set_pad_top(&style_container, 0);
    lv_style_set_pad_bottom(&style_container, 0);
    lv_style_set_pad_left(&style_container, 0);
    lv_style_set_pad_right(&style_container, 0);
    lv_style_set_bg_opa(&style_container, 0);
    lv_style_set_border_width(&style_container, 0);
    lv_style_set_width(&style_container, lv_pct(100));
    lv_style_set_height(&style_container, LV_SIZE_CONTENT);

    lv_style_init(&style_button);
    lv_style_set_pad_top(&style_button, 4);
    lv_style_set_pad_bottom(&style_button, 4);
    lv_style_set_pad_left(&style_button, 4);
    lv_style_set_pad_right(&style_button, 4);
    lv_style_set_radius(&style_button, 6);
    lv_style_set_text_color(&style_button, lv_palette_main(LV_PALETTE_TEAL));

    lv_style_init(&style_button_active);
    lv_style_set_bg_color(&style_button_active, lv_palette_main(LV_PALETTE_TEAL));
    lv_style_set_bg_opa(&style_button_active, LV_OPA_100);
    lv_style_set_text_color(&style_button_active, lv_color_black());
}

void init_screen_home(void) {
    screen_home = lv_scr_act();
    lv_obj_add_style(screen_home, &style_screen, 0);
    use_flex_column(screen_home);

    label_volume_home = lv_label_create(screen_home);
    lv_label_set_text(label_volume_home, "Ergohaven");

    label_time = lv_label_create(screen_home);
    lv_label_set_text(label_time, "Planeta");
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_48, LV_PART_MAIN);

    lv_obj_t *mods = lv_obj_create(screen_home);
    lv_obj_add_style(mods, &style_container, 0);
    use_flex_row(mods);

    label_gui   = create_button(mods, "GUI", &style_button, &style_button_active);
    label_alt   = create_button(mods, "ALT", &style_button, &style_button_active);
    label_ctrl  = create_button(mods, "CTL", &style_button, &style_button_active);
    label_shift = create_button(mods, "SFT", &style_button, &style_button_active);

    lv_obj_t *bottom_row = lv_obj_create(screen_home);
    lv_obj_add_style(bottom_row, &style_container, 0);

    label_layer = lv_label_create(bottom_row);
    lv_label_set_text(label_layer, "");
    lv_obj_align(label_layer, LV_ALIGN_LEFT_MID, 20, 0);
    display_process_layer_state(0);

    label_layout = lv_label_create(bottom_row);
    lv_label_set_text(label_layout, "");
    lv_obj_align(label_layout, LV_ALIGN_RIGHT_MID, -20, 0);

    label_caps = create_button(screen_home, "CAPS", &style_button, &style_button_active);
}

void init_screen_volume(void) {
    screen_volume = lv_obj_create(NULL);
    lv_obj_add_style(screen_volume, &style_screen, 0);

    arc_volume = lv_arc_create(screen_volume);
    lv_obj_set_size(arc_volume, 200, 200);
    lv_obj_center(arc_volume);

    label_volume_arc = lv_label_create(screen_volume);
    lv_label_set_text(label_volume_arc, "00");
    lv_obj_set_style_text_font(label_volume_arc, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_center(label_volume_arc);

    lv_obj_t *volume_text_label = lv_label_create(screen_volume);
    lv_label_set_text(volume_text_label, "Volume");
    lv_obj_align(volume_text_label, LV_ALIGN_BOTTOM_MID, 0, -50);
}

void init_screen_media(void) {
    screen_media = lv_obj_create(NULL);
    lv_obj_add_style(screen_media, &style_screen, 0);
    use_flex_column(screen_media);
    lv_obj_set_flex_align(screen_media, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    label_media_artist = lv_label_create(screen_media);
    lv_label_set_text(label_media_artist, "N/A");
    lv_label_set_long_mode(label_media_artist, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_artist, lv_pct(90));
    lv_obj_set_style_text_align(label_media_artist, LV_TEXT_ALIGN_CENTER, 0);

    label_media_title = lv_label_create(screen_media);
    lv_label_set_text(label_media_title, "N/A");
    lv_label_set_long_mode(label_media_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_title, lv_pct(90));
    lv_obj_set_style_text_align(label_media_title, LV_TEXT_ALIGN_CENTER, 0);
}

bool display_init_kb(void) {
    display_enabled = false;
    dprint("display_init_kb - start\n");

    setPinOutput(GP18);
    writePinHigh(GP18);

    painter_device_t display = qp_st7789_make_spi_device(240, 300, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);
    qp_set_viewport_offsets(display, 0, 20);

    if (!qp_init(display, QP_ROTATION_180) || !qp_power(display, true) || !qp_lvgl_attach(display)) return display_enabled;

    dprint("display_init_kb - initialised\n");

    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_TEAL), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);
    init_styles();

    init_screen_home();
    init_screen_volume();
    init_screen_media();
    display_enabled = true;

    return display_enabled;
}

void set_layout_label(uint8_t layout) {
    switch (layout) {
        case LANG_EN:
            lv_label_set_text(label_layout, "EN");
            lang_sync_external(LANG_EN);
            break;

        case LANG_RU:
            lv_label_set_text(label_layout, "RU");
            lang_sync_external(LANG_RU);
            break;
    }
}

void read_string(uint8_t *data, char *string_data) {
    uint8_t data_length = data[1];
    memcpy(string_data, data + 2, data_length);
    string_data[data_length] = '\0';
}

void start_home_screen_timer(void) {
    dprint("start_home_screen_timer\n");
    home_screen_timer = timer_read();
}

void display_process_raw_hid_data(uint8_t *data, uint8_t length) {
    uint8_t data_type = data[0];
    char    string_data[length - 2];
    dprintf("display_process_raw_hid_data - received data_type %u \n", data_type);
    switch (data_type) {
        case _TIME:
            dprintf("time %02d:%02d\n", data[1], data[2]);
            lv_label_set_text_fmt(label_time, "%02d:%02d", data[1], data[2]);
            break;

        case _VOLUME:
            dprintf("volume %d\n", data[1]);
            lv_label_set_text_fmt(label_volume_home, "Vol: %02d%%", data[1]);
            lv_label_set_text_fmt(label_volume_arc, "%02d", data[1]);
            lv_arc_set_value(arc_volume, data[1]);
            lv_scr_load(screen_volume);
            start_home_screen_timer();
            break;

        case _LAYOUT:
            dprintf("layout %d\n", data[1]);
            set_layout_label(data[1]);
            break;

        case _MEDIA_ARTIST:
            read_string(data, string_data);
            dprintf("media artist %s\n", string_data);
            lv_label_set_text(label_media_artist, string_data);
            lv_scr_load(screen_media);
            start_home_screen_timer();
            break;

        case _MEDIA_TITLE:
            read_string(data, string_data);
            dprintf("media title %s\n", string_data);
            lv_label_set_text(label_media_title, string_data);
            lv_scr_load(screen_media);
            start_home_screen_timer();
            break;
    }
}

void display_process_layer_state(uint8_t layer) {
    switch (layer) {
        case _DEF:
            lv_label_set_text(label_layer, "BASE");
            break;
        case _NAV:
            lv_label_set_text(label_layer, "NAV");
            break;
        case _SYM:
            lv_label_set_text(label_layer, "SYMBOL");
            break;
        case _ADJ:
            lv_label_set_text(label_layer, "ADJ");
            break;
        case _FOURTH:
            lv_label_set_text(label_layer, "4");
            break;
        case _FIFTH:
            lv_label_set_text(label_layer, "5");
            break;
        case _SIXTH:
            lv_label_set_text(label_layer, "6");
            break;
        case _SEVENTH:
            lv_label_set_text(label_layer, "7");
            break;
        case _EIGHTH:
            lv_label_set_text(label_layer, "8");
            break;
        case _NINTH:
            lv_label_set_text(label_layer, "9");
            break;
        case _TENTH:
            lv_label_set_text(label_layer, "10");
            break;
        case _ELEVENTH:
            lv_label_set_text(label_layer, "11");
            break;
        case _TWELTH:
            lv_label_set_text(label_layer, "12");
            break;
        case _THIRTEENTH:
            lv_label_set_text(label_layer, "13");
            break;
        case _FOURTEENTH:
            lv_label_set_text(label_layer, "14");
            break;
        case _FIFTEENTH:
            lv_label_set_text(label_layer, "15");
            break;
    }
}

void display_housekeeping_task(void) {
    if (home_screen_timer && timer_elapsed(home_screen_timer) > 5000) {
        home_screen_timer = 0;
        lv_scr_load(screen_home);
    }

    toggle_state(label_shift, LV_STATE_PRESSED, MODS_SHIFT);
    toggle_state(label_ctrl, LV_STATE_PRESSED, MODS_CTRL);
    toggle_state(label_alt, LV_STATE_PRESSED, MODS_ALT);
    toggle_state(label_gui, LV_STATE_PRESSED, MODS_GUI);
}

void display_process_caps(bool active) {
    toggle_state(label_caps, LV_STATE_PRESSED, active);
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
    dprintf("raw_hid_receive - received %u bytes \n", length);

    // if (is_display_enabled()) {
        display_process_raw_hid_data(data, length);
    // } else if (is_keyboard_master() && !is_display_side()) {
        // dprint("RPC_ID_USER_HID_SYNC \n");
        // transaction_rpc_send(RPC_ID_USER_HID_SYNC, length, data);
    // }
}

void hid_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (is_display_enabled()) {
        display_process_raw_hid_data((uint8_t *)initiator2target_buffer, initiator2target_buffer_size);
    }
}

// void keyboard_post_init_user() {
    // sync received hid data
    // transaction_register_rpc(RPC_ID_USER_HID_SYNC, hid_sync);
// }

layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_display_enabled()) {
        display_process_layer_state(get_highest_layer(state));
    }
    //   #if defined(AUDIO_ENABLE)
    //     static bool is_base_on = false;
    // if (layer_state_cmp(state, _BASE) != is_base_on) {
    //         is_base_on = layer_state_cmp(state, _BASE);
    //         if (is_base_on) {
    //             stop_all_notes();
    //         } else {
    //             PLAY_SONG(base_sound);
    //         }
    //     }
    // #endif
    return state;
}
