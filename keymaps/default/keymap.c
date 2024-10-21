// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum { // Tapdance declarations
  TapHold_COMMA,
  TapHold_DOT
};

enum custom_keycodes {
  // Marco declarations
  MC_CNQ = SAFE_RANGE,
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
const uint16_t PROGMEM combo_enter[] = {TD(TapHold_COMMA), TD(TapHold_DOT), COMBO_END};
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
    COMBO(combo_sel_sen, MC_SEL_SEN),
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
                SEND_STRING(SS_TAP(X_GRV) SS_TAP(X_LBRC) SS_TAP(X_GRV) SS_TAP(X_RBRC) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_DOWN) SS_TAP(X_DOWN));
            }
            return true; // Skip all further processing of this key
        case MC_SEL_SEN: // select the whole sentence
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
            }
            return true; // Skip all further processing of this key
        case TD(TapHold_COMMA): case TD(TapHold_DOT):
            // action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            action = tap_dance_get(QK_TAP_DANCE_GET_INDEX(keycode));
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
        default:
            return true; // Process all other keycodes normally
    }
};

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
    [TapHold_COMMA] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMMA, LCA(KC_COMMA)),
    [TapHold_DOT]   = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, LGUI(KC_DOT))
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) { // for OSL() to work properly
    if (IS_QK_ONE_SHOT_MOD(keycode) && is_oneshot_layer_active() && record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    return;
}

// Automatically enable sniping-mode on the pointer layer.
#define AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define ENCODER_MAP_KEY_DELAY 10
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [4] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [5] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};

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
    [0] = LAYOUT_ortho_10x5 (
        KC_1,         KC_2,         KC_3,         KC_4,         KC_5,    KC_6,    KC_7,         KC_8,         KC_9,         KC_0,
        KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,    KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_S), LSFT_T(KC_F), KC_G,    KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_QUOTE),
        KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    KC_N,    KC_M,         TD(TapHold_COMMA),  TD(TapHold_DOT),   KC_SLASH,
                                    LT(3,KC_SPC), KC_LSFT,      KC_MPLY, KC_BSPC, LT(1,KC_ENT), LT(2,KC_DEL)
    ),
    // LAYER_NUM 1
    [1] = LAYOUT_ortho_10x5 (
        _______, _______, _______, _______, _______,  _______,       _______,       _______,       _______,       _______,
        KC_BSPC, KC_7,    KC_8,    KC_9,    KC_EQUAL, KC_BTN4,       KC_BTN5,       KC_VOLU,       KC_VOLD,       KC_MPLY,
        KC_PAST, KC_4,    KC_5,    KC_6,    KC_PMNS,   _______,       OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI),
        KC_PSLS, KC_1,    KC_2,    KC_3,    KC_PPLS,  LALT(KC_PGUP), LALT(KC_PGDN), LSG(KC_S),     LALT(KC_F4),   (KC_TAB),
                          KC_0,    KC_PDOT, KC_MPLY,  TO(0),         _______,       LGUI(KC_TAB)
    ),
    // LAYER_SYMBOL 2
    [2] = LAYOUT_ortho_10x5 (
        _______, _______, _______, _______, _______,          _______,      _______,        _______,    _______,       _______,
        KC_GRV,  KC_LBRC, KC_LPRN, KC_LCBR, LCTL(KC_EXLM),    LSFT(KC_GRV), LSFT(KC_BSLS),  LSFT(KC_7), MC_CNQ,        KC_EQL,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_MINS,      LSFT(KC_COMMA), LSFT(KC_6), LSFT(KC_DOT),  LSFT(KC_8),
        KC_BSLS, KC_RBRC, KC_RPRN, KC_RCBR, LCTL(KC_QUES),    LSFT(KC_EQL), LSFT(KC_MINS),  KC_SCLN,    LSFT(KC_SCLN), LSFT(KC_SLSH),
                          _______, _______, _______,          TO(0),        _______,        _______
    ),
    // LAYER_NAVI 3
    [3] = LAYOUT_ortho_10x5 (
        _______, _______, _______, _______,       _______,       _______, _______, _______, _______, _______,
        KC_MPLY, KC_VOLD, KC_VOLU, KC_BTN4,       KC_BTN5,       KC_F11,  KC_F12,  _______, _______, _______,
        KC_HOME, KC_LEFT, KC_UP,   KC_RGHT,       KC_END,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_PGDN, KC_PGUP, KC_DOWN, LALT(KC_PGUP), LALT(KC_PGDN), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
                          _______, _______,       _______,       TO(0),   _______, _______
    ),
    // LAYER_POINTER 4
    [4] = LAYOUT_ortho_10x5 (
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, KC_BTN3, TO(0),   _______, _______
    ),
    // LAYER_GAMING
    [5] = LAYOUT_ortho_10x5 (
        _______, _______, _______, _______, KC_T,   _______, _______, _______, _______, _______,
        KC_Q,    KC_W,    KC_C,    KC_E,    KC_R,   _______, _______, _______, _______, _______,
        KC_TAB,  KC_A,    KC_W,    KC_D,    KC_G,   _______, _______, _______, _______, _______,
        KC_Z,    KC_X,    KC_S,    KC_V,    KC_B,   _______, _______, _______, _______, _______,
                          KC_SPC,  KC_LSFT, KC_ESC, TO(0),   KC_F12,  _______
    )
};
