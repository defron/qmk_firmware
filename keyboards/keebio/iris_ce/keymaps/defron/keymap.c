// Copyright 2024 Kevin Thomer (aka defron)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/achordion.h"

#define K_MREP LCTL_T(QK_REP)
#define K_MAREP LCTL_T(QK_AREP)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance declarations
enum {
    TD_X_MO,
};


enum layers {
     _QWERTY,
     _NAV,
     _UTIL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,   KC_A,    KC_S,   KC_D, LCTL_T(KC_F), KC_G,                            KC_H, RCTL_T(KC_J), KC_K, RALT_T(KC_L), KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     K_MAREP,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LGUI,     LT(_NAV,KC_ESC), KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH, QK_LEAD,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   KC_F12, TD(TD_X_MO), KC_SPC,               RSFT_T(KC_ENT), KC_BSPC, KC_RALT 
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,  KC_PGUP, KC_VOLD, KC_MS_U, KC_VOLU, KC_PGDN,                            KC_PIPE, KC_UNDS,  KC_UP,  KC_F11,  KC_F12,  KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,  KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                            KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    K_MREP,  KC_LALT, KC_ACL0, KC_ACL1, KC_ACL2, TT(_UTIL), KC_TRNS,         KC_TRNS, KC_DEL,  KC_BTN1, KC_BTN3,  KC_BTN2, KC_BSLS, KC_TRNS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_UTIL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_DEL,   KC_F9,  KC_F10,  KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,   KC_NO,   KC_NO,   KC_NO,  KC_PSCR,  KC_NO,                            KC_PMNS,   KC_7,    KC_8,    KC_9,   KC_SLSH, RGB_TOG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,   KC_NO,                            KC_PPLS,   KC_4,    KC_5,    KC_6,   KC_PAST, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     EE_CLR,  KC_LALT,  KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,          KC_ESC,  KC_PDOT,  KC_1,    KC_2,    KC_3,   KC_BSPC, KC_TRNS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,  KC_0,   KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};


bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    return keycode != K_MREP && keycode != K_MAREP && keycode != TD(TD_X_MO); // must not remember the magic key itself
}

bool repeat_preseed = false;
bool alt_repeat_preseed = false;
uint8_t previous_layer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case K_MREP:
            if (!repeat_preseed && record->tap.count && record->event.pressed) {
                if (get_repeat_key_count()) {
                    return true;
                }
                repeat_preseed = true;
                repeat_key_invoke(&record->event);
                return false;        // Return false to ignore further processing of key
            } else if (repeat_preseed && record->tap.count && record->event.pressed == false)  {
                if (get_repeat_key_count()) {
                    return true;
                }
                repeat_preseed = false;
                repeat_key_invoke(&record->event);
                return false;        // Return false to ignore further processing of key
            }
            break;
        case K_MAREP:
            if (!alt_repeat_preseed && record->tap.count && record->event.pressed) {
                if (get_repeat_key_count()) {
                    return true;
                }
                alt_repeat_preseed = true;
                alt_repeat_key_invoke(&record->event);
                return false;        // Return false to ignore further processing of key
            } else if (alt_repeat_preseed && record->tap.count && record->event.pressed == false)  {
                if (get_repeat_key_count()) {
                    return true;
                }
                alt_repeat_preseed = false;
                alt_repeat_key_invoke(&record->event);
                return false;        // Return false to ignore further processing of key
            }
            break;
    }
    if (!process_achordion(keycode, record)) { return false; }
    return true;
}

void matrix_scan_user(void) {
  achordion_task();
}

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
	NULL // Null terminate the array of overrides!
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RCTL_T(KC_J):
        case LCTL_T(KC_F):
        case RALT_T(KC_L):
            return 260;
        case LT(_NAV,KC_ESC):
            return 180;
        case TD(TD_X_MO):
            return 300;
        case KC_LSFT:
            return 250;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RCTL_T(KC_J):
        case LCTL_T(KC_F):
        case RALT_T(KC_L):
            return 130;
        case LT(_NAV,KC_ESC):
        case K_MREP:
        case K_MAREP:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_ENT):
        case K_MAREP:
        case K_MREP:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_W)) {
        // Leader, w => windows ctrl + alt + del
        tap_code16(LCTL(LALT(KC_DEL)));
    } else if (leader_sequence_one_key(KC_C)) {
        // Leader, c => Ctrl + Shift + C
        SEND_STRING(SS_LCTL(SS_LSFT("c")));
    } else if (leader_sequence_one_key(KC_V)) {
        // Leader, v => Ctrl + Shift + V
        SEND_STRING(SS_LCTL(SS_LSFT("v")));
    } else if (leader_sequence_one_key(KC_F12)) {
        // Leader, f12 => find all references
        SEND_STRING(SS_LALT(SS_LSFT(SS_TAP(X_F12))));
    } else if (leader_sequence_two_keys(KC_K, KC_C)) {
        // Leader, k, c => comment out block
        SEND_STRING(SS_LCTL("kc"));
    } else if (leader_sequence_two_keys(KC_K, KC_U)) {
        // Leader, k, u => uncomment block
        SEND_STRING(SS_LCTL("ku"));
    } else if (leader_sequence_one_key(KC_SPC)) {
        // Leader, SPACE => base layer
        layer_move(_QWERTY);
    } else if (leader_sequence_two_keys(KC_SPC, KC_SPC)) {
        // Leader, SPACE, SPACE => nav layer
        layer_move(_NAV);
    } else if (leader_sequence_three_keys(KC_SPC, KC_SPC, KC_SPC)) {
        // Leader, SPACE, SPACE, SPACE => utility layer
        layer_on(_NAV);
        layer_on(_UTIL);
    }
}

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        return TD_TRIPLE_TAP;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    uint8_t curr_layer = get_highest_layer(layer_state);
    switch (xtap_state.state) {
        case TD_SINGLE_HOLD:
            previous_layer = curr_layer;
            if(curr_layer == _QWERTY) {
                layer_move(_NAV);
            } else {
                layer_move(_QWERTY);
            }
            break;
        case TD_SINGLE_TAP:
            layer_move(_QWERTY);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_NAV);
            break;
        case TD_TRIPLE_TAP:
            layer_on(_NAV);
            layer_on(_UTIL);
            break;
        default:
            break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_HOLD:
            layer_move(previous_layer);
            if (previous_layer == _UTIL) {
                layer_on(_NAV);
            }
            break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_X_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case TD(TD_X_MO):
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}