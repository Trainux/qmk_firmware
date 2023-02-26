/*
Copyright 2020 Evy Dekkers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// LED INDEXES FOR THE UNDERGLOW LIGHTS
#define RGB_MATRIX_UNDERGLOW_LED_INDEXES 0,1,2,3,4,34,35,36,37,38
// IN HSV FORMAT
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_NUMERIC_KEYS HSV_CYAN
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ALPHA_KEYS HSV_WHITE
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_CAPS_KEYS HSV_PINK
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_MENU_KEYS HSV_YELLOW
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_NOT_DEFINED_KEYS HSV_OFF
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_FN_KEYS HSV_BLUE
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ENTER_KEYS HSV_GREEN
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DELETE_KEYS HSV_RED
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_WINDOW_KEYS HSV_PURPLE
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_SPACE_KEYS HSV_ORANGE
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_PROGRAMABLE_KEYS HSV_MAGENTA
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DEFAULT HSV_RED
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_UNDERGLOW HSV_ORANGE
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_CONFIG_KEYS HSV_YELLOW
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ARROW_KEYS HSV_GOLD
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_TAB_KEYS RGB_MATRIX_CUSTOM_PERSONALIZED_KC_SPACE_KEYS
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ESC_KEYS RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DELETE_KEYS
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ALT_KEYS HSV_BLUE
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_CNTRL_KEYS RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ALT_KEYS
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_MEDIA_KEYS HSV_MAGENTA
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DEBUG_KEYS HSV_RED
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_MACRO_KEYS HSV_MAGENTA
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_SPECIAL_CHARACTERS_KEYS 100,255,255
#define RGB_MATRIX_CUSTOM_PERSONALIZED_KC_FUNCTIONS_KEYS HSV_GOLD


RGB_MATRIX_EFFECT(PERSONALIZED_KC_COLORS)
RGB_MATRIX_EFFECT(PERSONALIZED_KC_COLORS_BREATHING)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#if defined(ENABLE_RGB_MATRIX_CUSTOM_PERSONALIZED_KC_COLORS) || defined(PERSONALIZED_KC_COLORS_BREATHING)

    uint8_t active_layer = 0;
    keypos_t personalized_kc_led_index_key_position[RGB_MATRIX_LED_COUNT];

    HSV  personalizes_kc_led_index_hsv_position [NUM_KEYMAP_CUSTOM_LAYERS][RGB_MATRIX_LED_COUNT];
    bool enabled_breathing = false;

    uint8_t underglow_led_indexes[] = {RGB_MATRIX_UNDERGLOW_LED_INDEXES};
    uint8_t underglow_led_indexes_length = sizeof(underglow_led_indexes) / sizeof(underglow_led_indexes[0]);

    void PERSONALIZED_KC_COLORS_set_active_layer(uint8_t active_layer_sended)
    {
        active_layer = active_layer_sended;
    }

    static bool PERSONALIZED_KC_COLORS_is_underglow_led(uint8_t led_index)
    {
        for(uint8_t i = 0; i < underglow_led_indexes_length; i++)
        {
            if (underglow_led_indexes[i] == led_index)
            {
                return true;
            }
        }

        return false;
    }

    static bool PERSONALIZED_KC_COLORS_is_alpha_key(uint16_t keycode)
    {
        return ((keycode >= KC_A && keycode <= KC_Z) || keycode == KC_NUHS || keycode == KC_SCLN || keycode == KC_BSLS ||  keycode == KC_PIPE);
    }

    static bool PERSONALIZED_KC_COLORS_is_numeric_key(uint16_t keycode)
    {
        return (keycode >= KC_1 && keycode <= KC_0) || (keycode >= KC_KP_1 && keycode <= KC_KP_0);
    }

    static bool PERSONALIZED_KC_COLORS_is_fn_key(uint16_t keycode)
    {
        return (keycode >= KC_F1 && keycode <= KC_F12);
    }

    static bool PERSONALIZED_KC_COLORS_is_caps_key(uint16_t keycode)
    {
        return (keycode == KC_LSFT || keycode == KC_RSFT || keycode == KC_CAPS);
    }

    static bool PERSONALIZED_KC_COLORS_is_menu_key(uint16_t keycode)
    {
        return (keycode == MO(1) || keycode == MO(2) || keycode == MO(3));
    }

    static bool PERSONALIZED_KC_COLORS_is_transparent_key(uint16_t keycode)
    {
        return (keycode == KC_TRNS);
    }

    static bool PERSONALIZED_KC_COLORS_is_keycode_not_defined(uint16_t keycode)
    {
        return (keycode == KC_NO);
    }

    static bool PERSONALIZED_KC_COLORS_is_enter_key(uint16_t keycode)
    {
        return keycode == KC_ENT;
    }

    static bool PERSONALIZED_KC_COLORS_is_delete_key(uint16_t keycode)
    {
        return keycode == KC_DEL || keycode == KC_BSPC;
    }

    static bool PERSONALIZED_KC_COLORS_is_windows_key(uint16_t keycode)
    {
        return keycode == KC_LGUI || keycode == KC_RGUI || keycode == KC_APP;
    }

    static bool PERSONALIZED_KC_COLORS_is_space_key(uint16_t keycode)
    {
        return keycode == KC_SPC;
    }

    static bool PERSONALIZED_KC_COLORS_is_programable_button(uint16_t keycode)
    {
        return keycode >= PB_1 && keycode <= PB_32;
    }

    static bool PERSONALIZED_KC_COLORS_is_config_key(uint16_t keycode)
    {
        return keycode == RGB_TOG || keycode == RGB_MOD || keycode == RGB_HUI
            || keycode == RGB_HUD || keycode == RGB_SAI || keycode == RGB_SAD
            || keycode == RGB_VAI || keycode == RGB_VAD || keycode == RGB_RMOD;
    }

    static bool PERSONALIZED_KC_COLORS_is_arrow_key(uint16_t keycode)
    {
        return keycode == KC_LEFT || keycode == KC_DOWN || keycode == KC_UP
            || keycode == KC_RGHT;
    }

    static bool PERSONALIZED_KC_COLORS_is_tab_key(uint16_t keycode)
    {
        return keycode == KC_TAB;
    }

    static bool PERSONALIZED_KC_COLORS_is_esc_key(uint16_t keycode)
    {
        return keycode == KC_ESC;
    }

    static bool PERSONALIZED_KC_COLORS_is_alt_key(uint16_t keycode)
    {
        return keycode == KC_LALT || keycode == KC_RALT;
    }

    static bool PERSONALIZED_KC_COLORS_is_cntrl_key(uint16_t keycode)
    {
        return keycode == KC_LCTL || keycode == KC_RCTL;
    }

    static bool PERSONALIZED_KC_COLORS_is_debug_key(uint16_t keycode)
    {
        return keycode == QK_BOOT || keycode == EE_CLR || keycode == DB_TOGG || keycode == KC_PWR;
    }

    static bool PERSONALIZED_KC_COLORS_is_macro_key(uint16_t keycode)
    {
        return keycode == KC_NUM || keycode == KC_MYCM || keycode == KC_CALC || keycode == KC_AGIN || keycode == KC_UNDO || keycode == KC_CUT || keycode == KC_COPY || keycode == KC_PSTE;
    }

    static bool PERSONALIZED_KC_COLORS_is_special_character_key(uint16_t keycode)
    {
        return keycode == KC_GRV || keycode == KC_MINS || keycode == KC_QUOT
            || keycode == KC_COMM || keycode == KC_DOT || keycode == KC_SLSH
            || keycode == KC_LBRC || keycode == KC_EXLM || keycode == KC_AT
            || keycode == KC_HASH || keycode == KC_DLR || keycode == KC_PERC
            || keycode == KC_CIRC || keycode == KC_AMPR || keycode == KC_ASTR
            || keycode == KC_LPRN || keycode == KC_RPRN || keycode == KC_TILD
            || keycode == KC_UNDS || keycode == KC_PLUS || keycode == KC_LCBR
            || keycode == KC_RCBR || keycode == KC_EQL || keycode == KC_RBRC
            || keycode == KC_NUBS || keycode == KC_PSLS || keycode == KC_PAST
            || keycode == KC_PMNS || keycode == KC_PPLS || keycode == KC_PDOT
            || keycode == KC_PEQL;
    }

    static bool PERSONALIZED_KC_COLORS_is_media_key(uint16_t keycode)
    {
        return keycode == KC_MPRV || keycode == KC_MNXT || keycode == KC_MSTP || keycode == KC_MPLY;
    }

    static bool PERSONALIZED_KC_COLORS_is_function_key(uint16_t keycode)
    {
        return keycode == KC_PSCR || keycode == KC_SCRL || keycode == KC_PAUS
            || keycode == KC_INS || keycode == KC_HOME || keycode == KC_PGUP
            || keycode == KC_END || keycode == KC_PGDN;
    }

    void PERSONALIZED_KC_matrix_set_color(HSV hsv_configured, uint8_t led_index, uint8_t  current_layer)
    {
        bool caps_lock = host_keyboard_led_state().caps_lock;
        HSV hsv_matrix_config = rgb_matrix_config.hsv;
        HSV hsv = {hsv_configured.h, hsv_matrix_config.s, hsv_matrix_config.v};
        bool isOff = hsv_configured.h == 0 && hsv_configured.s == 0 && hsv_configured.v == 0;
        bool isWhite = hsv_configured.h == 0 && hsv_configured.s == 0 && hsv_configured.v == 255;
        bool is_caps_led = false;

        if (isOff)
        {
            hsv.h = 5;
            hsv.s = 5;
            hsv.v = 0;
        }
        else if(isWhite)
        {
            hsv.h = 5;
            hsv.s = 5;
            hsv.v = hsv_matrix_config.v;
        }

        // if caps_lock is active, enable breathing efect only for shift and cap keys
        if (caps_lock)
        {
            uint16_t keycode = keymap_key_to_keycode(current_layer, personalized_kc_led_index_key_position[led_index]);

            if (PERSONALIZED_KC_COLORS_is_transparent_key(keycode) && current_layer > 0)
            {
                // maybe a transparent key is a caps/shift key
                PERSONALIZED_KC_matrix_set_color(hsv_configured, led_index, current_layer - 1);
                return;

            }else if( PERSONALIZED_KC_COLORS_is_caps_key(keycode))
            {
                is_caps_led = true;
            }
        }

        if(!isOff && ((enabled_breathing && !is_caps_led) || (!enabled_breathing && is_caps_led)))
        {
            uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
            hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
        }

        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
    }

    void PERSONALIZED_KC_COLORS_initialize_color_led_matrix(uint8_t initial_layer, uint8_t current_layer, uint8_t led_index)
    {
        uint16_t keycode = keymap_key_to_keycode(current_layer, personalized_kc_led_index_key_position[led_index]);
        HSV hsv_configured = {  };

        if (PERSONALIZED_KC_COLORS_is_underglow_led(led_index))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_UNDERGLOW};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_alpha_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ALPHA_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_numeric_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_NUMERIC_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_fn_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_FN_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_caps_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_CAPS_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_menu_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_MENU_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_enter_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ENTER_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_delete_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DELETE_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_windows_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_WINDOW_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_space_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_SPACE_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_programable_button(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_PROGRAMABLE_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_config_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_CONFIG_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_arrow_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ARROW_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_esc_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ESC_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_tab_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_TAB_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_special_character_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_SPECIAL_CHARACTERS_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_alt_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_ALT_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_cntrl_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_CNTRL_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_media_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_MEDIA_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_debug_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DEBUG_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_macro_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_MACRO_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_function_key(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_FUNCTIONS_KEYS};
            hsv_configured = t_hsv;
        }
        else if (PERSONALIZED_KC_COLORS_is_transparent_key(keycode))
        {
            if (current_layer > 0) // 0 layer
            {
                PERSONALIZED_KC_COLORS_initialize_color_led_matrix(initial_layer, current_layer - 1, led_index);
                return;
            }
            else // TO AVOID RECURRENT CALLS
            {
                HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DEFAULT};
                hsv_configured = t_hsv;
            }
        }
        else if (PERSONALIZED_KC_COLORS_is_keycode_not_defined(keycode))
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_NOT_DEFINED_KEYS};
            hsv_configured = t_hsv;
        } else
        {
            HSV t_hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_DEFAULT};
            hsv_configured = t_hsv;
        }

        personalizes_kc_led_index_hsv_position[initial_layer][led_index] = hsv_configured;
    }

    static void PERSONALIZED_KC_COLORS_render_underglow_leds(void)
    {
        for(uint8_t i = 0; i < underglow_led_indexes_length; i++)
        {
            HSV hsv = {RGB_MATRIX_CUSTOM_PERSONALIZED_KC_UNDERGLOW};
            PERSONALIZED_KC_matrix_set_color(hsv, underglow_led_indexes[i], active_layer);
        }
    }

    static bool PERSONALIZED_KC_COLORS_render_matrix(effect_params_t* params)
    {
        RGB_MATRIX_USE_LIMITS(led_min, led_max);

        for (uint8_t i = led_min; i < led_max; i++)
        {
            RGB_MATRIX_TEST_LED_FLAGS();

            HSV hsv = personalizes_kc_led_index_hsv_position[active_layer][i];
            PERSONALIZED_KC_matrix_set_color(hsv, i, active_layer);
        }

        PERSONALIZED_KC_COLORS_render_underglow_leds();

        return rgb_matrix_check_finished_leds(led_max);
    }

    static void PERSONALIZED_KC_COLORS_init(bool enable_breathing)
    {
        PERSONALIZED_KC_COLORS_set_active_layer(0);

        enabled_breathing = enable_breathing;

        for (uint8_t row = 0; row < MATRIX_ROWS; row++)
        {
            for (uint8_t col = 0; col < MATRIX_COLS; col++)
            {
                uint8_t led_index = g_led_config.matrix_co[row][col];
                if (led_index != NO_LED)
                {
                    personalized_kc_led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};

                    for(uint8_t layer_index = 0; layer_index < NUM_KEYMAP_CUSTOM_LAYERS; layer_index++)
                    {
                        PERSONALIZED_KC_COLORS_initialize_color_led_matrix(layer_index, layer_index, led_index);
                    }
                }
            }
        }

#if defined(CONSOLE_ENABLE)
            uprintf("EL UNDERGLOW LENGTH: %2u\n", underglow_led_indexes_length);
            uprintf("VALOR DEL ARRAY: ");
            for(uint8_t i = 0; i < underglow_led_indexes_length; i++)
            {
                uprintf("VALOR DEL ARRAY: %2u", underglow_led_indexes[i]);
            }
            uprintf("\n");
#endif

    }

    static bool PERSONALIZED_KC_COLORS(effect_params_t* params)
    {
        if (params->init)
        {
            PERSONALIZED_KC_COLORS_init(false);
        }

        return PERSONALIZED_KC_COLORS_render_matrix(params);
    }

    static bool PERSONALIZED_KC_COLORS_BREATHING(effect_params_t* params)
    {
        if (params->init)
        {
            PERSONALIZED_KC_COLORS_init(true);
        }

        return PERSONALIZED_KC_COLORS_render_matrix(params);
    }

#endif
#endif
