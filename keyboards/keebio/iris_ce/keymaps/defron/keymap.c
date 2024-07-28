// Copyright 2024 Kevin Thomer (aka defron)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "transactions.h"

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
void mo_esc_finished(tap_dance_state_t *state, void *user_data);
void mo_esc_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance declarations
enum {
    TD_X_MO,
    TD_MO_ESC,
};


enum layers {
     _QWERTY,
     _NAV,
     _UTIL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   QK_LEAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,   KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_A, LALT_T(KC_S), KC_D, LCTL_T(KC_F), KC_G,                           KC_H, RCTL_T(KC_J), KC_K, RALT_T(KC_L), KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     K_MAREP,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LGUI,     TD(TD_MO_ESC), KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_LBRC,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   KC_F12, TD(TD_X_MO), KC_SPC,               RSFT_T(KC_ENT), KC_BSPC, KC_RALT 
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,  KC_PGUP, KC_VOLD, KC_MS_U, KC_VOLU, KC_PGDN,                            KC_PIPE, KC_UNDS,  KC_UP,  KC_RCBR, KC_F11,  KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,  KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                            KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     K_MREP, KC_LALT, KC_ACL0, KC_ACL1, KC_ACL2, TT(_UTIL), KC_TRNS,         KC_TRNS, KC_DEL,  KC_BTN1, KC_BTN3,  KC_BTN2, KC_BSLS, KC_RBRC,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_UTIL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     QK_BOOT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   EE_CLR,                             KC_F6,   KC_F7,   KC_DEL,   KC_F9,  KC_F10,  KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,   KC_NO,   KC_NO,   KC_NO,  KC_PSCR,  KC_NO,                            KC_PMNS,   KC_7,    KC_8,    KC_9,   KC_SLSH, RGB_TOG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,   KC_NO,                            KC_PPLS,   KC_4,    KC_5,    KC_6,   KC_PAST, KC_TRNS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS,  KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,         KC_TRNS,  KC_PDOT,  KC_1,    KC_2,    KC_3,   KC_BSPC,  KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_ENT,   KC_0,   KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};


bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    return keycode != K_MREP && keycode != K_MAREP && keycode != TD(TD_X_MO); // must not remember the overloaded keys
}

bool repeat_preseed = false;
bool alt_repeat_preseed = false;
uint8_t previous_layer = 0;
bool momentary_layer = false;
bool capsword_active = false;
bool leader_active = false;

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
        case LALT_T(KC_S):
            return 230;
        case TD(TD_MO_ESC):
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
        case LALT_T(KC_S):
            return 130;
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
    leader_active = true;
}

void leader_end_user(void) {
    leader_active = false;
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
        SEND_STRING(SS_LSFT(SS_TAP(X_F12)));
    } else if (leader_sequence_one_key(KC_J)) {
        // Leader, j => ctrl + left arrow
        SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
    } else if (leader_sequence_one_key(KC_L)) {
        // Leader, l => ctrl + right arrow
        SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
    } else if (leader_sequence_one_key(KC_COMM)) {
        // Leader, comma => alt + left arrow
        SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
    } else if (leader_sequence_one_key(KC_DOT)) {
        // Leader, comma => alt + right arrow
        SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
    } else if (leader_sequence_two_keys(KC_K, KC_C)) {
        // Leader, k, c => comment out block
        SEND_STRING(SS_LCTL("kc"));
    } else if (leader_sequence_two_keys(KC_K, KC_U)) {
        // Leader, k, u => uncomment block
        SEND_STRING(SS_LCTL("ku"));
    } else if (leader_sequence_one_key(KC_SPC)) {
        // Leader, SPACE => base layer
        previous_layer = 0;
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
            momentary_layer = true;
            previous_layer = curr_layer;
            if(curr_layer == _QWERTY) {
                layer_move(_NAV);
            } else {
                layer_move(_QWERTY);
            }
            break;
        case TD_SINGLE_TAP:
            layer_move(_QWERTY);
            previous_layer = 0;
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
            momentary_layer = false;
            layer_move(previous_layer);
            if (previous_layer == _UTIL) {
                layer_on(_NAV);
            }
            break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void mo_esc_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    uint8_t curr_layer = get_highest_layer(layer_state);
    switch (xtap_state.state) {
        case TD_SINGLE_HOLD:
            momentary_layer = true;
            previous_layer = curr_layer;
            if(curr_layer == _QWERTY) {
                layer_move(_NAV);
            } else {
                layer_move(_QWERTY);
            }
            break;
        case TD_SINGLE_TAP:
            register_code(KC_ESC);
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

void mo_esc_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_HOLD:
            momentary_layer = false;
            layer_move(previous_layer);
            if (previous_layer == _UTIL) {
                layer_on(_NAV);
            }
            break;
        case TD_SINGLE_TAP:
            unregister_code(KC_ESC);
            break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_X_MO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_MO_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mo_esc_finished, mo_esc_reset)
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_MINS:
        case KC_UNDS:
        case TD(TD_X_MO):
        case TD(TD_MO_ESC):
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    
    const uint8_t layer = get_highest_layer(layer_state);
    const uint8_t azure_hue = 148;
    const uint8_t orange_hue = 17;
    const uint8_t green_hue = 64;
    const uint8_t cyan_hue = 127;
    const uint8_t violet_hue = 180;

    const uint8_t mods = get_mods();
    const uint8_t o_s_mods = get_oneshot_mods();

    HSV hsv;
    hsv.s = 255;
    hsv.v = 100;

    if (mods & MOD_MASK_CTRL || o_s_mods & MOD_MASK_CTRL) {
        const uint8_t ctrl = g_led_config.matrix_co[3][0];
        hsv.h = cyan_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(ctrl, rgb.r, rgb.g, rgb.b);
    }
    if (!capsword_active && (mods & MOD_MASK_SHIFT || o_s_mods & MOD_MASK_SHIFT)) {
        const uint8_t shft = g_led_config.matrix_co[2][0];
        hsv.h = cyan_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(shft, rgb.r, rgb.g, rgb.b);
    }
    if (capsword_active) {
        const uint8_t capsword = g_led_config.matrix_co[2][0];
        hsv.h = violet_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(capsword, rgb.r, rgb.g, rgb.b);
    }
    if (mods & MOD_MASK_ALT || o_s_mods & MOD_MASK_ALT) {
        const uint8_t alt = g_led_config.matrix_co[9][2];
        hsv.h = cyan_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(alt, rgb.r, rgb.g, rgb.b);
    }
    if (mods & MOD_MASK_GUI || o_s_mods & MOD_MASK_GUI) {
        const uint8_t super = g_led_config.matrix_co[4][5];
        hsv.h = cyan_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(super, rgb.r, rgb.g, rgb.b);
    }
    if (leader_active) {
        const uint8_t leader = g_led_config.matrix_co[5][0];
        hsv.h = violet_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(leader, rgb.r, rgb.g, rgb.b);
    }


    if (!layer && !previous_layer)
        return false;

    uint8_t index = 0;
    bool color_base = false;
    
    if (layer) {
        index = g_led_config.matrix_co[0][1 + layer];
        hsv.h = momentary_layer ? azure_hue : green_hue;
    } else {
        index = g_led_config.matrix_co[0][1 + previous_layer];
        color_base = true;
        hsv.h = orange_hue;
    }

    if (index < led_min || index >= led_max)
        return false;

    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);

    if(color_base) {
        const uint8_t base = g_led_config.matrix_co[0][1];
        hsv.h = azure_hue;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(base, rgb.r, rgb.g, rgb.b);
    }

    return false;
}

void caps_word_set_user(bool active) {
    if (active) {
        capsword_active = true;
    } else {
        capsword_active = false;
    }
}

//TODO: if I swap super and leader I should remove this
void leader_rgb_sync_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    memcpy(&leader_active, in_data, in_buflen);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_RPC_LEADER_SYNC, leader_rgb_sync_handler);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {

        bool needs_sync = false;
        static uint16_t last_sync = false;
        static bool last_state = false;

        if (memcmp(&leader_active, &last_state, sizeof(last_state))) {
            needs_sync = true;
            memcpy(&last_state, &leader_active, sizeof(last_state));
        }

        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(USER_RPC_LEADER_SYNC, sizeof(leader_active), &leader_active)) {
                last_sync = timer_read32();
            }
        }
    }
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {  // Was Ctrl held?
        switch (keycode) {
            case KC_Y: return C(KC_Z);
            case KC_Z: return C(KC_Y);
            case KC_C: return C(KC_V);
            case KC_W: return C(S(KC_T));
            case KC_T: return C(KC_W);
        }
    }
    bool shifted = (mods & MOD_MASK_SHIFT);
    switch (keycode) {
        case KC_TAB:
            if (shifted) {
                return KC_TAB;
            } else {
                return S(KC_TAB);
            }
        case KC_DOT:
            if (shifted) {
                return KC_LT;
            }
        case KC_COMM:
            if (shifted) {
                return KC_GT;
            }
        case KC_0:
            if (shifted) {
                return KC_LPRN;
            } else {
                return KC_1;
            }
        case KC_1:
            if (shifted) {
                return KC_RPRN;
            } else {
                return KC_0;
            }
        case KC_EQL:
            if (shifted) {
                return KC_MINS;
            }
        case KC_MINS:
            return KC_PLUS;
    }

    return KC_TRNS;  // Defer to default definitions.
}