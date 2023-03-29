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
#include "keymap_user_config.h"

typedef struct {
    char c1_r;
    char c1_g;
    char c1_b;
    
    char c2_r;
    char c2_g;
    char c2_b;
    
    char c3_r;
    char c3_g;
    char c3_b;
} user_config_t;

user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.c1_r = 0x44;  // purple
    user_config.c1_g = 0x00;
    user_config.c1_b = 0xff;
    
    user_config.c2_r = 0xff;  // pink
    user_config.c2_g = 0x00;
    user_config.c2_b = 0x4f;
 
    user_config.c3_r = 0x00;  // green
    user_config.c3_g = 0xff;
    user_config.c3_b = 0x00;
    eeconfig_update_user_datablock(&user_config);
}

void user_config_read(void) {
    eeconfig_read_user_datablock(&user_config);
}

void user_config_write(void) {
    eeconfig_update_user_datablock(&user_config);
}

char user_config_c1_r(void) { return user_config.c1_r; }
char user_config_c1_g(void) { return user_config.c1_g; }
char user_config_c1_b(void) { return user_config.c1_b; }

char user_config_c2_r(void) { return user_config.c2_r; }
char user_config_c2_g(void) { return user_config.c2_g; }
char user_config_c2_b(void) { return user_config.c2_b; }

char user_config_c3_r(void) { return user_config.c3_r; }
char user_config_c3_g(void) { return user_config.c3_g; }
char user_config_c3_b(void) { return user_config.c3_b; }

void user_config_set_c1(char r, char g, char b) {
    user_config.c1_r = r;
    user_config.c1_g = g;
    user_config.c1_b = b;
    user_config_write();
}