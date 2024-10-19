// Copyright 2024 Kai H. Chang (@kaihchang)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// rotary encoder
#define ENCODER_RESOLUTION 4
#define ENCODER_A_PINS { A0 }
#define ENCODER_B_PINS { A1 }

// analog joystick
#define ANALOG_JOYSTICK_X_AXIS_PIN { A4 }
#define ANALOG_JOYSTICK_Y_AXIS_PIN { A2 }

// SSD1306 OLED display
#define MY_I2C_ADDRESS (0x3C << 1)
#ifdef OLED_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 10000
#endif

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the joystick.  See also:
// - `AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
    #define AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, \
              k42, k43, k44, k45, k46, k47            \
) { \
    { k00,   k01,   k02, k03, k04, k05, k06, k07, k08,   k09   }, \
    { k10,   k11,   k12, k13, k14, k15, k16, k17, k18,   k19   }, \
    { k20,   k21,   k22, k23, k24, k25, k26, k27, k28,   k29   }, \
    { k30,   k31,   k32, k33, k34, k35, k36, k37, k38,   k39   }, \
    { KC_NO, KC_NO, k42, k43, k44, k45, k46, k47, KC_NO, KC_NO }  \
}
