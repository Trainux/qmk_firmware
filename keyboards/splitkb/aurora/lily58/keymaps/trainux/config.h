/* Copyright 2022 splitkb.com <support@splitkb.com>
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

#pragma once

// #ifdef RGBLIGHT_ENABLE
//  #   define RGBLIGHT_EFFECT_BREATHING
//  #   define RGBLIGHT_EFFECT_SNAKE
// #endif


#define NUM_KEYMAP_CUSTOM_LAYERS 4
// #define SPLIT_LAYER_STATE_ENABLE
// #define SPLIT_MODS_ENABLE
// #define SPLIT_OLED_ENABLE
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_DEFAULT_VAL 20 // Sets the default brightness value, if none has been set
#define SPLIT_LAYER_STATE_ENABLE // This enables syncing of the layer state between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the currently active layer.
#define SPLIT_LED_STATE_ENABLE // This enables syncing of the Host LED status (caps lock, num lock, etc) between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the Host LED status.
#define SPLIT_MODS_ENABLE // This enables transmittng modifier state (normal, weak and oneshot) to the non primary side of the split keyboard. The purpose of this feature is to support cosmetic use of modifer state (e.g. displaying status on an OLED screen).
#define SPLIT_OLED_ENABLE // This enables transmitting the current OLED on/off status to the slave side of the split keyboard. The purpose of this feature is to support state (on/off state only) syncing.
#define SPLIT_WPM_ENABLE // This enables transmitting the current WPM to the slave side of the split keyboard. The purpose of this feature is to support cosmetic use of WPM (e.g. displaying the current value on an OLED screen).
// #define MASTER_LEFT

// #define USE_I2C
// #define SOFT_SERIAL_PIN D0

//#define SPLIT_TRANSACTION_IDS_KB KB_MODE_SYNC
//#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_RBG_MATRIX_MODE


#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended

//#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN	// Enables RGB_MATRIX_GRADIENT_UP_DOWN
//#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #define ENABLE_RGB_MATRIX_BREATHING
// #define ENABLE_RGB_MATRIX_BAND_SAT
// #define ENABLE_RGB_MATRIX_BAND_VAL
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
//#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON // MOLA
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// #define ENABLE_RGB_MATRIX_DUAL_BEACON
// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS // MOLA
// #define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #define ENABLE_RGB_MATRIX_HUE_BREATHING
// #define ENABLE_RGB_MATRIX_HUE_PENDULUM
// #define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
// #define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
//#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_MULTISPLASH

// #define ENABLE_RGB_MATRIX_CUSTOM_KC_COLORS
// #define RGB_MATRIX_CUSTOM_EFFECT_IMPLS
// #define RGB_MATRIX_CUSTOM_RGB_CUSTOM_KC
#define ENABLE_RGB_MATRIX_CUSTOM_PERSONALIZED_KC_COLORS
#define ENABLE_RGB_MATRIX_CUSTOM_PERSONALIZED_KC_COLORS_BREATHING

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS




