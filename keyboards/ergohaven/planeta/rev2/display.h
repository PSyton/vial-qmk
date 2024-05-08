#include "qp_lvgl.h"


bool is_display_enabled(void);
bool display_init_kb(void);
bool display_init_user(void);
void display_housekeeping_task(void);
void display_process_caps(bool active);
void display_process_raw_hid_data(uint8_t *data, uint8_t length);
void display_process_layer_state(uint8_t layer);
