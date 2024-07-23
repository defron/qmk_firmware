// Copyright 2024 Kevin Thomer (aka defron)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/achordion.h"

#define K_MREP LCTL_T(QK_REP)
#define K_MAREP LCTL_T(QK_AREP)


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
                                     KC_F12, TT(_NAV), KC_SPC,               RSFT_T(KC_ENT), KC_BSPC, KC_RALT
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
                                 TO(_QWERTY), KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_UTIL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_DEL,   KC_F9,  KC_F10,  KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,   KC_NO,   KC_NO,   KC_NO,  KC_PSCR,  KC_NO,                            KC_PMNS,   KC_7,    KC_8,    KC_9,   KC_SLSH, RGB_TOG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,   KC_NO,                            KC_PPLS,   KC_4,    KC_5,    KC_6,   KC_PAST, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     EE_CLR,  KC_LALT,  KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,          KC_ESC,  KC_PDOT,  KC_1,    KC_2,    KC_3,   KC_BSPC, KC_TRNS,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                TO(_QWERTY), TO(_NAV), KC_TRNS,                   KC_TRNS,   KC_0,  KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};


bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    return keycode != K_MREP && keycode != K_MAREP; // must not remember the magic key itself
}

bool repeat_preseed = false;
bool alt_repeat_preseed = false;

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