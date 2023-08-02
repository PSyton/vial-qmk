# MCU name
MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040

# Bootloader selection
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no

# Build Options
AUDIO_ENABLE = yes           # Audio output
AUDIO_DRIVER = pwm_hardware
