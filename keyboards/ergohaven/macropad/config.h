#pragma once

#define VIAL_KEYBOARD_UID {0xBB, 0x17, 0xF0, 0x5B, 0x02, 0x80, 0x1D, 0x1D}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 2 }

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#define I2C1_SCL_PIN        GP11
#define I2C1_SDA_PIN        GP10
#define OLED_BRIGHTNESS 128
#define I2C_DRIVER I2CD1
#endif
