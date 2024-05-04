MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040
# ALLOW_WARNINGS = yes
# PICO_INTRINSICS_ENABLED = no

DEFAULT_FOLDER = ergohaven/velvet/rev2

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor

SRC += keyboards/ergohaven/ergohaven_rgb.c keyboards/ergohaven/ergohaven.c keyboards/ergohaven/lang_ru_en.c
