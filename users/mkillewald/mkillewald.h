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

#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Begin chunk copied from keychron_ft.h
#define KEY_PRESS_STEP_0 (0x1 << 0)
#define KEY_PRESS_STEP_1 (0x1 << 1)
#define KEY_PRESS_STEP_2 (0x1 << 2)
#define KEY_PRESS_STEP_3 (0x1 << 3)
#define KEY_PRESS_STEP_4 (0x1 << 4)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_STEP_0 | KEY_PRESS_STEP_1 | KEY_PRESS_STEP_2)
#define KEY_PRESS_LED_TEST (KEY_PRESS_STEP_0 | KEY_PRESS_STEP_3 | KEY_PRESS_STEP_4)

enum {
    LED_TEST_MODE_OFF,
    LED_TEST_MODE_WHITE,
    LED_TEST_MODE_RED,
    LED_TEST_MODE_GREEN,
    LED_TEST_MODE_BLUE,
    LED_TEST_MODE_MAX
} led_test_mode;

extern uint16_t key_press_status;
extern uint32_t timer_3s_buffer;
#ifdef SPLIT_KEYBOARD
#    ifdef RGB_MATRIX_ENABLE
extern uint8_t led_state;
extern uint8_t light_test_state;
extern HSV     hsv;
#    endif
#endif
// End chunk copied from keychron_ft.h

enum my_bootloader_state {
    BOOTLOADER_INACTIVE,
    BOOTLOADER_PRESSED,
    BOOTLOADER_WAIT,
    BOOTLOADER_DO
} bootloader_state;

enum my_keycodes {
    KC_LIGHT_TAB_TOGGLE = QK_USER_0,
    KC_LIGHT_ALPHAS_TOGGLE,
    KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE,
    KC_FN_LAYER_COLOR_TOGGLE,
    KC_LOCK_BLANK_MAC,
    KC_CYBER_COLORS_TOGGLE
};

#define KC_LTTOG KC_LIGHT_TAB_TOGGLE
#define KC_LATOG KC_LIGHT_ALPHAS_TOGGLE
#define KC_TKTOG KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE
#define KC_FCTOG KC_FN_LAYER_COLOR_TOGGLE
#define KC_LBMAC KC_LOCK_BLANK_MAC
#define KC_CYTOG KC_CYBER_COLORS_TOGGLE

void housekeeping_task_mkillewald(void);
bool process_record_mkillewald(uint16_t keycode, keyrecord_t *record);

void housekeeping_task_keychron_ft(void);
#endif