// Copyright 2024 Kai H. Chang (@kaihchang)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// set to 0 if debounce isn't needed
#define DEBOUNCE 5

#define ONESHOT_TIMEOUT 5000

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

// rotary encoder
#define ENCODER_RESOLUTION 4
#define ENCODER_A_PINS { GP26 }
#define ENCODER_B_PINS { GP27 }
#define TAP_CODE_DELAY 10

// analog joystick
#define ANALOG_JOYSTICK_X_AXIS_PIN GP28
#define ANALOG_JOYSTICK_Y_AXIS_PIN GP29
#define ANALOG_JOYSTICK_AUTO_AXIS
#define JOYSTICK_AXIS_COUNT 2
#define ANALOG_JOYSTICK_SPEED_REGULATOR 20 // lower makes it go faster
#define ANALOG_JOYSTICK_READ_INTERVAL 10
#define ANALOG_JOYSTICK_SPEED_MAX 2
#define POINTING_DEVICE_DEBUG // debug messages will be shown in console

// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// #define AUTO_MOUSE_TIME 650 // time layer remains active after activation

// Set the mouse settings to a comfortable speed/accuracy trade-off,
// assuming a screen refresh rate of 60 Htz or higher
// The default is 50. This makes the mouse ~3 times faster and more accurate
#define MOUSEKEY_INTERVAL 16
// The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// give it more time to accelerate to max speed to retain precise control over short distances.
#define MOUSEKEY_TIME_TO_MAX 40
// The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
#define MOUSEKEY_DELAY 100
// It makes sense to use the same delay for the mouseweel
#define MOUSEKEY_WHEEL_DELAY 100
// The default is 100
#define MOUSEKEY_WHEEL_INTERVAL 50
// The default is 40
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

// SSD1306 OLED display
#define I2C_DRIVER I2CD0
#define OLED_DISPLAY_128X64
#define I2C0_SDA_PIN GP20 // I2C0 SDA
#define I2C0_SCL_PIN GP21 // I2C0 SCL
// #define MY_I2C_ADDRESS (0x3C << 1)
#define OLED_TIMEOUT 30000
