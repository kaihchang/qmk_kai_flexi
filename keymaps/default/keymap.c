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

// Tapdance declarations
enum {
    TH_COMM = SAFE_RANGE,
    TH_DOT,
    MC_CNQ,
    MC_SEL_SEN
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

/* COMBOS */
const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_manager[] = {KC_Q, KC_E, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_backspace[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_backspace2[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_delete[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_delete2[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_enter[] = {TD(TH_COMM), TD(TH_DOT), COMBO_END};
const uint16_t PROGMEM combo_sel_sen[] = {RSFT_T(KC_J), RGUI_T(KC_QUOTE), COMBO_END};
const uint16_t PROGMEM combo_tg_num[] = {KC_BSPC, LT(1,KC_ENT), COMBO_END};
const uint16_t PROGMEM combo_tg_nav[] = {LT(3,KC_SPC), KC_LSFT, COMBO_END};
const uint16_t PROGMEM combo_tg_game[] = {KC_G, KC_M, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_manager, RCS(KC_ESC)),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_backspace, KC_BSPC),
    COMBO(combo_delete, KC_DEL),
    COMBO(combo_enter, KC_ENT),
    COMBO(combo_sel_en, MC_SEL_SEN),
    COMBO(combo_tg_num, TG(1)),
    COMBO(combo_tg_nav, TG(3)),
    COMBO(combo_tg_game, TG(5)),
};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;
    switch (keycode) {
        case MC_CNQ: // output 「」
            if (record->event.pressed) {
                // when keycode MC_CNQ is pressed
                SEND_STRING("「」" SS_TAP(KC_LEFT));
            } else {
                // when keycode MC_CNQ is released
            }
            break;
        case MC_SEL_SEN: // select the whole sentence
            if (record->event.pressed) {
                // when keycode MC_SEL_SEN is pressed
                SEND_STRING(SS_TAP(KC_HOME) SS_LSFT(KC_END));
            } else {
                // when keycode MC_SEL_SEN is released
            }
            break;
        // case TD(TH_COMM):
        // case TD(TH_DOT):
    }
    return true;
};

// Automatically enable sniping-mode on the pointer layer.
#define AUTO_SNIPING_ON_LAYER LAYER_POINTER

#if defined (ENCODER_ENABLE) && (ENCODER_MAP_ENABLE)
#define ENCODER_MAP_KEY_DELAY 10
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_QWERTY]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_NUMBER]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_SYMBOL]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_NAVI]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_POINTER] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [LAYER_GAMING]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
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
     * │   │   │SPC│NUM│PAU|BSC|SYM|DEL|   |   |
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [LAYER_QWERTY] = LAYOUT(
        KC_1,         KC_2,         KC_3,         KC_4,         KC_5,    KC_6,    KC_7,         KC_8,         KC_9,         KC_0,
        KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,    KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_S), LSFT_T(KC_F), KC_G,    KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RATL_T(KC_L), RGUI_T(KC_QUOTE),
        KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    KC_N,    KC_M,         TD(TH_COMM),  TD(TH_DOT),   KC_SLASH,
                                    LT(3,KC_SPC), KC_LSFT,      KC_MPLY, KC_BSPC, LT(1,KC_ENT), LT(2,KC_DEL)
    ),

    [LAYER_NUMBER] = LAYOUT(
        _______, _______, _______, _______, _______,  _______,       _______,       _______,       _______,       _______,
        KC_BSPC, KC_7,    KC_8,    KC_9,    KC_EQUAL, KC_BTN4,       KC_BTN5,       KC_VOLU,       MS_VOLD,       MS_MPLY,
        KC_PAST, KC_4,    KC_5,    KC_6,    KC_MNS,   _______,       OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI),
        KC_PSLS, KC_1,    KC_2,    KC_3,    KC_PPLS,  LALT(KC_PGUP), LALT(KC_PGDN), LSG(KC_S),     LALT(KC_F4),   (KC_TAB),
                          KC_0,    KC_PDOT, KC_MPLY,  TO(0),         _______,       LGUI(KC_TAB)
    ),

    [LAYER_SYMBOL] = LAYOUT(
        _______, _______, _______, _______, _______,          _______,      _______,        _______,    _______,       _______,
        KC_GRV,  KC_LBRC, KC_LPRN, KC_LCBR, LCTL(KC_EXLM),    LSHT(KC_GRV), LSHT(KC_BSLS),  LSHT(KC_7), MC_CNQ,        KC_EQL,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_MINS,      LSHT(KC_COMMA), LSHT(KC_6), LSHT(KC_DOT),  LSHT(KC_8),
        KC_BSLS, KC_RBRC, KC_RPRN, KC_RCBR, LCTL(KC_QUES),    LSHT(KC_EQL), LSHT(KC_MINS),  KC_SCLN,    LSHT(KC_SCLN), LSHT(KC_SLSH),
                          _______, _______, _______,          TO(0),        _______,        _______,
    ),

    [LAYER_NAVI] = LAYOUT(
        _______, _______, _______, _______,       _______,       _______, _______, _______, _______, _______,
        MS_MPLY, MS_VOLD, MS_VOLU, KC_BTN4,       KC_BTN5,       KC_F11,  KC_F12,  _______, _______, _______,
        KC_HOME, KC_LEFT, KC_UP,   KC_RGHT,       KC_END,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_PGDN, KC_PGUP, KC_DOWN, LALT(KC_PGUP), LALT(KC_PGDN), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
                          _______, _______,       _______,       TO(0),   _______, _______,
    ),

    [LAYER_POINTER] = LAYOUT(
        _______, _______, _______, _______, _______,          _______,      _______,        _______,    _______,       _______,
        KC_Q, KC_W, KC_E,    KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,     KC_O,   KC_P,
        KC_A, KC_S, MS_BTN1,    MS_BTN2,   KC_G,    KC_H,    KC_J,   KC_K,     KC_L,   KC_QUOTE,
        KC_Z, KC_X, KC_C,    KC_V,   KC_B,    KC_N,    KC_M,   KC_COMMA, KC_DOT, KC_SLASH,
                    LT(3,KC_SPC), TO(0), KC_MPLY, KC_BSPC, KC_LSFT, KC_DEL
    ),

    [LAYER_GAMING] = LAYOUT(
        _______, _______, _______, _______, KC_T,   _______, _______, _______, _______, _______,
        KC_Q,    KC_W,    KC_C,    KC_E,    KC_R,   _______, _______, _______, _______, _______,
        KC_TAB,  KC_A,    KC_W,    KC_D,    KC_G,   _______, _______, _______, _______, _______,
        KC_Z,    KC_X,    KC_S,    KC_V,    KC_B,   _______, _______, _______, _______, _______,
                          KC_SPC,  KC_LSHT, KC_ESC, TO(0),   KC_F12,  _______
    )
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) { // for OSL() to work properly
    if (IS_QK_ONE_SHOT_MOD(keycode) && is_oneshot_layer_active() && record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    return;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TH_COMM] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, LCA(KC_COMM)),
    [TH_DOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, LGUI(KC_DOT))
};