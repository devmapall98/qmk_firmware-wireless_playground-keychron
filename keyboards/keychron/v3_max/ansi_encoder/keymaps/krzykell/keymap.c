/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

enum custom_keycodes {
    MACRO_0 = SAFE_RANGE,
    MACRO_1,
    KC_4SPC,
    ALT_INV,
    ALT_TGL,
    ALT_PRS
};

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

bool is_alt_inv        = false;
bool is_alt_tgl        = false;
bool is_crntly_hld     = false;
bool is_crntly_tgl     = false;
bool alt_tgl_conf      = false;
bool alt_tgl_conf_flag = false;

int rgb_keys_1[2] = {34, 35};
int rgb_keys_2[2] = {36, 37};
int rgb_keys_3[3] = {64, 65, 78};
int rgb_keys_4[6] = {64, 65, 78, 80, 71, 72};

#define KC_SRCH  (LGUI(KC_SPC))
#define TASKMGR  (LCTL(LSFT(KC_ESC)))
#define MUTEMIC  (LCTL(LSFT(LGUI(KC_M))))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,     KC_MUTE,    KC_PSCR,  MUTEMIC,  DF(WIN_BASE),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,              KC_UP,
        KC_LCTL,  KC_LGUI,  ALT_PRS,                                KC_SPC,                                 KC_RALT,  KC_RGUI,  TT(MAC_FN), KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_tkl_ansi(
        TASKMGR,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     _______,    _______,  _______,  _______,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,  _______,
        KC_NUM,   RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,              _______,
        _______,  GU_TOGG,  ALT_INV,                                KC_4SPC,                                ALT_TGL,  GU_TOGG,  _______,    _______,    MACRO_0,  _______,  MACRO_1),

    [WIN_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,    KC_PSCR,  MUTEMIC,  DF(MAC_BASE),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,              KC_UP,
        KC_LCTL,  KC_LGUI,  ALT_PRS,                                KC_SPC,                                 KC_RALT,  KC_RGUI,  TT(WIN_FN), KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RIGHT),

    [WIN_FN] = LAYOUT_tkl_ansi(
        TASKMGR,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_SRCH,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    _______,    KC_P7,    KC_P8,    KC_P9,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  KC_PAST,  _______,  KC_P0,    KC_PMNS,  KC_PPLS,    _______,    KC_P4,    KC_P5,    KC_P6,
        _______,  DM_PLY1,  DM_REC1,  DM_PLY2,  DM_REC2,  DM_RSTP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    KC_P0,      KC_P1,    KC_P2,    KC_P3,
        KC_NUM,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  _______,              KC_PENT,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  KC_PCMM,  KC_PDOT,  KC_PSLS,              _______,              _______,
        _______,  GU_TOGG,  ALT_INV,                                KC_4SPC,                                ALT_TGL,  GU_TOGG,  _______,    _______,    MACRO_0,  _______,  MACRO_1),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
    [MAC_FN]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

// clang-format on
// MACROS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case MACRO_0: //Send left arrow symbol
            if (record->event.pressed) {
                SEND_STRING("<-");
            }
            return false;
            break;

        case MACRO_1: //Send right arrow symbol
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            return false;
            break;

        case KC_4SPC: //Send 4 spaces (poor mans TAB)
            if (record->event.pressed && get_mods() & MOD_MASK_SHIFT)    {
                SEND_STRING("    ");
            }
            return false;
            break;

        case ALT_INV: //Invert behavior of LALT: it's registered while it's not pressed and unregistered temporarily when pressed
            if (record->event.pressed) {
                if (is_alt_inv == false) {
                    if (is_alt_tgl == false) {
                        is_alt_inv = true;
                        register_code(KC_LALT);
                    } else { //Repurpose the key when it's not used to configure behavior of ALT_TGL
                        if (alt_tgl_conf == false) {
                            alt_tgl_conf = true;
                        } else {
                            alt_tgl_conf = false;
                        }
                    }
                } else {
                    is_alt_inv = false;
                    unregister_code(KC_LALT);
                }
            }
            return false;
            break;
        
        case ALT_TGL: //Toggle LALT: Press once to keep it registered, press again to keep it unregistered
            if (record->event.pressed) {
                if (is_alt_tgl == false) {
                    if (is_alt_inv == false) {
                        is_alt_tgl = true;
                    }
                } else {
                    is_alt_tgl = false;
                }
            }
            return false;
            break;

        case ALT_PRS: //Replacement LALT keycode for ALT_INV and ALT_TGL to work properly without disrupting default LALT behavior
            if (record->event.pressed) { //LALT is pressed
                if (is_alt_inv == false && is_alt_tgl == false) {
                    register_code(KC_LALT);
                } else if (is_alt_inv == true && is_alt_tgl == false) {
                    unregister_code(KC_LALT);
                } else if (is_alt_inv == false && is_alt_tgl == true) {
                    if (is_crntly_tgl == false) {
                        is_crntly_tgl = true;
                        alt_tgl_conf_flag = true;
                        register_code(KC_LALT);
                    } else {
                        if (alt_tgl_conf == false) { //Unregister on release
                            is_crntly_hld = true;
                        } else { //Unregister on press
                            is_crntly_hld = true;
                            alt_tgl_conf_flag = false;
                            unregister_code(KC_LALT);
                        }
                    }
                }
            } else { //LALT is released
                if (is_alt_inv == false && is_alt_tgl == false) {
                    unregister_code(KC_LALT);
                } else if (is_alt_inv == true && is_alt_tgl == false) {
                    register_code(KC_LALT);
                } else if (is_alt_inv == false && is_alt_tgl == true) {
                    if (is_crntly_tgl == false) {
                        is_crntly_tgl = true;
                        alt_tgl_conf_flag = true;
                        register_code(KC_LALT);
                    } else {
                        if (alt_tgl_conf == false) { //Unregister on release
                            if (is_crntly_hld == true) {
                                is_crntly_tgl = false;
                                is_crntly_hld = false;
                                alt_tgl_conf_flag = false;
                                unregister_code(KC_LALT);
                            }
                        } else { // Unregister on press
                            if (is_crntly_hld == true) {
                                is_crntly_hld = false;
                                is_crntly_tgl = false;
                            }
                        }
                    }
                }
            }


    }
    return true;
}
// END MACROS

// Key Matrix to LED Index
// ESC      {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, __, 13, 14, 15 },
// GRAVE    { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 },
// TAB      { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
// CAPS     { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, __, __, __, __ },
// LSHFT    { 63, __, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, __, __, 75, __ },
// LCTRL    { 76, 77, 78, __, __, __, 79, __, __, __, 80, 81, 82, 83, 84, 85, 86 },

// START COLOR STUFF
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Set "MAC" layers to a predefined (in color.h) color
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
            case 1:
                rgb_matrix_set_color(i, RGB_SICKYELLOW);
                break;
            default:
                break;
        }
    }

    // Set color for FN layers
    if (get_highest_layer(layer_state) == 1 || get_highest_layer(layer_state) == 3) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_INDIGO);
                }
            }
        }
        rgb_matrix_set_color(82, RGB_RED);
    }

    // Set color for dynamic macro keys
    if (get_highest_layer(layer_state) == 3) {
        for (int i = 0; i < 2; i++) {
            rgb_matrix_set_color(rgb_keys_1[i], RGB_USRORANGED);
        }
        for (int i = 0; i < 2; i++) {
            rgb_matrix_set_color(rgb_keys_2[i], RGB_USRORANGEL);
        }        
        rgb_matrix_set_color(38, RGB_RED);
    }

    // Set color of ALT_INV
    if (is_alt_inv == true) {
        for (int i = 0; i < 3; i++) {
            rgb_matrix_set_color(rgb_keys_3[i], RGB_RED);
        }
    }

    // Set color of ALT_TGL
    if (is_alt_tgl == true) {
        for (int i = 0; i < 6; i++) {
            rgb_matrix_set_color(rgb_keys_4[i], RGB_USRORANGEL);
        }
    }
    if (is_alt_tgl == true && alt_tgl_conf == true) {
        for (int i = 0; i < 3; i++) {
            rgb_matrix_set_color(rgb_keys_3[i], RGB_SPRINGGREEN);
        }
    }
    if (is_alt_tgl == true && is_crntly_tgl == true && alt_tgl_conf_flag == true) {
        for (int i = 0; i < 3; i++) {
            rgb_matrix_set_color(rgb_keys_3[i], RGB_RED);
        }
    }
    return false;
}
