#include <stdint.h>

struct hid_data_t {
    uint8_t hours;
    uint8_t minutes;
    bool    time_changed;
    uint8_t volume;
    bool    volume_changed;
    char    media_artist[256];
    bool    media_artist_changed;
    char    media_title[256];
    bool    media_title_changed;
};

struct hid_data_t get_hid_data(void);

void reset_hid_changed(void);
