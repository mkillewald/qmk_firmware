/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "keymap_user.h"
#include "keymap_user_config.h"

enum layers{
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

enum my_keycodes {
#ifdef VIA_ENABLE
    KC_CHGC1 = QK_KB_11,    // USER11 here gave compile error (not defined)
                            // indexed at 11 to appear after Keychron's keycodes
#else
    KC_CHGC1 = SAFE_RANGE,
#endif
    KC_CHGC2,
    KC_CHGC3
};

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_67(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPTN, KC_LCMMD,                           KC_SPC,                             KC_RCMMD, MO(_FN1), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_67(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL, KC_LWIN,  KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN2), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN1] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, KC_CHGC1, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______,  _______,            _______, _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______),

    [_FN2] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          RGB_TOG,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______,  _______,            _______, _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______),

    [_FN3] = LAYOUT_ansi_67(
        KC_TILD, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______, _______,
        _______, _______,  _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_FN2]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_FN3]     = { ENCODER_CCW_CW(_______, _______) },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) {
        return false;
    }
    
    switch (keycode) {
        case KC_CHGC1:
            if (record->event.pressed) {
                user_config_set_c1(0xff, 0xff, 0x00); // set c1 yellow, and save to eeprom
            }
            return false;  // Skip all further processing of this key         
        default:
            return true;  // Process all other keycodes normally
    }

    return true;
}

void keyboard_post_init_user(void) {
    user_config_read();
}

void rgb_matrix_init_user(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case MAC_BASE:
        case WIN_BASE:
            rgb_matrix_set_key_colors();
            break;
    }
    return false;
}

void rgb_matrix_set_key_colors(void) {
    
    // Q2 top row (minus esc)
    uint8_t toprow[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    for (uint8_t i = 0; i < sizeof(toprow)/sizeof(toprow[0]); i++) {
        rgb_matrix_set_color(toprow[i], user_config_c1_r(), user_config_c1_g(), user_config_c1_b());
    }           
    
    // Esc
    uint8_t accentkeys[] = {0};
    for (uint8_t i = 0; i < sizeof(accentkeys)/sizeof(accentkeys[0]); i++) {
        rgb_matrix_set_color(accentkeys[i], user_config_c2_r(), user_config_c2_g(), user_config_c2_b());                 
    }
    
    // Q2 qwerty row
    uint8_t secondrow[] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
    for (uint8_t i = 0; i < sizeof(secondrow)/sizeof(secondrow[0]); i++) {
        rgb_matrix_set_color(secondrow[i], user_config_c3_r(), user_config_c3_g(), user_config_c3_b());                 
    }
}