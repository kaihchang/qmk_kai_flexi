// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum custom_keycodes {
  LAYER_QWERTY = 0,
  LAYER_NUMBER,
  LAYER_SYMBOL,
  LAYER_NAVI,
  LAYER_POINTER,
  LAYER_GAMING
};

// Automatically enable sniping-mode on the pointer layer.
#define AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;
#    ifndef AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // AUTO_POINTER_LAYER_TRIGGER_ENABLE

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(A4, 900, 575, 285), // JOYSTICK_AXIS_IN(input_pin, low, rest, high)
    JOYSTICK_AXIS_IN(A2, 900, 575, 285)
};

#if defined(ENCODER_MAP_ENABLE)
#define ENCODER_MAP_KEY_DELAY 10
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* LAYER_QWERTY 0: default layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ' |
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B | N | M | , | . | / |
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │SHT│SPC│PAU|BSC|DEL|CTL|   |   |
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [LAYER_QWERTY] = LAYOUT(
        KC_1, KC_2, KC_3,    KC_4,   KC_5,    KC_6,    KC_7,   KC_8,     KC_9,   KC_0,
        KC_Q, KC_W, KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,     KC_O,   KC_P,
        KC_A, KC_S, KC_D,    KC_F,   KC_G,    KC_H,    KC_J,   KC_K,     KC_L,   KC_QUOTE,
        KC_Z, KC_X, KC_C,    KC_V,   KC_B,    KC_N,    KC_M,   KC_COMMA, KC_DOT, KC_SLASH,
                    KC_LSFT, KC_SPC, KC_MPLY, KC_BSPC, KC_DEL, KC_LCTL
    )
};