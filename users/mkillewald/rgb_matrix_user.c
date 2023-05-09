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
#include "myfork_keychron_ft.h"
#include "rgb_matrix_user.h"
#include "eeprom_user_config.h"
#include "layers.h"

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

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

__attribute__ ((weak))
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
  return false;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case MAC_BASE:
        case WIN_BASE:
#ifdef CAPS_LOCK_INDICATOR_COLOR
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);
            }
#endif
#ifdef CAPS_WORD_INDICATOR_COLOR
            if (is_caps_word_on()) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_word_indicator, CAPS_WORD_INDICATOR_COLOR);
            }
#endif
            break;
        case MAC_FN1:
        case WIN_FN1:
            set_fn1_layer_color(led_min, led_max, current_layer);
            break;
        case MAC_WIN_FN2:
            set_fn2_layer_color(led_min, led_max, current_layer);
            break;
    }
    rgb_matrix_indicators_advanced_myfork_keychron_ft(led_min, led_max);
    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}

void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

void set_fn1_layer_color(uint8_t led_min, uint8_t led_max, uint8_t current_layer) {
#ifdef FN1_LAYER_COLOR
    if (user_config_get_fn_layer_color_enable()) {
        rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_not_transparent, FN1_LAYER_COLOR);
    }
#endif
    check_fn_layer_transparent_keys_toggle(led_min, led_max, current_layer);
}

void set_fn2_layer_color(uint8_t led_min, uint8_t led_max, uint8_t current_layer) {
#ifdef FN2_LAYER_COLOR
    if (user_config_get_fn_layer_color_enable()) {
        rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_not_transparent, FN2_LAYER_COLOR);
    }
#endif
    check_fn_layer_transparent_keys_toggle(led_min, led_max, current_layer);
}

void check_fn_layer_transparent_keys_toggle(uint8_t led_min, uint8_t led_max, uint8_t current_layer) {
    if (user_config_get_fn_layer_transparent_keys_off()) {
        rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, RGB_OFF);
    }
}

bool is_caps_lock_indicator(uint16_t keycode) {
    bool indicator = keycode == KC_CAPS;

    if (user_config_get_caps_lock_light_tab()) {
        indicator = keycode == KC_TAB || keycode == KC_CAPS;
    }

    if (user_config_get_caps_lock_light_alphas()) {
        return (KC_A <= keycode && keycode <= KC_Z) || indicator;
    } else {
        return indicator;
    }
}

bool is_caps_word_indicator(uint16_t keycode) {
    bool indicator = keycode == KC_LSFT;
#ifdef CAPS_WORD_LIGHT_LOWER_LEFT_CORNER
    indicator = keycode == KC_LSFT || keycode == KC_LCTL || keycode == KC_LOPTN;
#endif
    return indicator;
}

bool is_transparent(uint16_t keycode) { return keycode == KC_TRNS; }
bool is_not_transparent(uint16_t keycode) { return keycode != KC_TRNS; }