MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040
# ALLOW_WARNINGS = yes
# PICO_INTRINSICS_ENABLED = no

# Build options
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
RGBLIGHT_ENABLE = yes

SRC += keyboards/ergohaven/ergohaven_rgb.c keyboards/ergohaven/ergohaven.c keyboards/ergohaven/lang_ru_en.c
