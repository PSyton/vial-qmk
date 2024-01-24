#pragma once

#define VIAL_KEYBOARD_UID {0xDE, 0x08, 0x99, 0xEF, 0xB2, 0xE4, 0xB3, 0x9E}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 2 }

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X64
#define I2C1_SCL_PIN        B6
#define I2C1_SDA_PIN        B7
#define OLED_BRIGHTNESS 128
#define I2C_DRIVER I2CD1
#endif

#define ENCODER_DIRECTION_FLIP
