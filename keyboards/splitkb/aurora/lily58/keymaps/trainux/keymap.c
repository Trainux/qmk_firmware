#include QMK_KEYBOARD_H
#include "print.h"
#include "transactions.h"
#include "quantum.h"
#include "wait.h"
#include "keyboard.h"
#include "split_util.h"
#include "timer.h"

enum layers {
  _DEFAULT = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
                        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
                        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_NUHS,
                        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_HOME,                KC_MUTE, KC_N, KC_M, KC_MINS, KC_EQL, KC_COMM, KC_DOT,
                            KC_LALT, KC_LGUI, MO(1), KC_SPC,                               KC_ENT,  MO(2), KC_RALT, KC_RCTL),

	[_LOWER] = LAYOUT(KC_TRNS, KC_MYCM, KC_F1, KC_F2, KC_F3, KC_F4,                            KC_MINS, KC_EQL, KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS,
                      KC_TRNS, KC_CALC, KC_F5, KC_F6, KC_F7, KC_F8,                            KC_LBRC, KC_RBRC, KC_INS, KC_HOME, KC_PGUP, KC_TRNS,
                      KC_TRNS, KC_CAPS, KC_F9, KC_F10, KC_F11, KC_F12,                         KC_QUOT, KC_NUHS, KC_DEL, KC_END, KC_PGDN, KC_RSFT,
                      KC_TRNS, KC_APP, KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, KC_TRNS,    KC_TRNS, KC_NUBS, KC_GRV, KC_SLSH, KC_CUT, KC_COPY, KC_PSTE,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, MO(3), KC_TRNS, KC_TRNS),

	[_RAISE] = LAYOUT(KC_TRNS, KC_MYCM, KC_F1, KC_F2, KC_F3, KC_F4,               KC_NO, KC_NUM, KC_P7, KC_P8, KC_P9, KC_PSLS,
                      KC_TRNS, KC_CALC, KC_F5, KC_F6, KC_F7, KC_F8,               KC_NO, KC_PEQL, KC_P4, KC_P5, KC_P6, KC_PAST,
                      KC_TRNS, KC_CAPS, KC_F9, KC_F10, KC_F11, KC_F12,               KC_NO, KC_UP, KC_P1, KC_P2, KC_P3, KC_PMNS,
                      KC_TRNS, KC_APP, KC_MPRV, KC_MNXT, KC_MSTP, KC_MPLY, KC_TRNS,    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PPLS,
                            KC_TRNS, KC_TRNS, MO(3), KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[_ADJUST] = LAYOUT(PB_1, PB_2, PB_3, PB_4, PB_5, PB_6,                                      PB_7, PB_8, PB_9, PB_10, PB_11, PB_12,
                       PB_13, PB_14, PB_15, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PWR,                               KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
                       QK_BOOT, EE_CLR, DB_TOGG, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

// static bool render_indicators = false;

extern void PERSONALIZED_KC_COLORS_set_active_layer(uint8_t active_layer_sended);

typedef struct _master_to_slave_t {
    int m2s_data;
} master_to_slave_t;

typedef struct _slave_to_master_t {
    int s2m_data;
} slave_to_master_t;

void user_sync_a_slave_handler (uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    slave_to_master_t *s2m = (slave_to_master_t*)out_data;
    s2m->s2m_data = m2s->m2s_data + 5; // whatever comes in, add 5 so it can be sent back
}

// void rpc_mode_sync_callback(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
//     if (m2s_size == sizeof(render_indicators)) {
//         memcpy(&render_indicators, m2s_buffer, m2s_size);
//     }
// }

void keyboard_post_init_user(void) {
    debug_enable=true;
   debug_matrix=true;

    PERSONALIZED_KC_COLORS_set_active_layer(_DEFAULT);
    //transaction_register_rpc(KB_MODE_SYNC, rpc_mode_sync_callback);

    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PERSONALIZED_KC_COLORS);
    HSV hsv = {HSV_BLUE};
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
}

//void housekeeping_task_user(void) {

    // if (!is_transport_connected())
    // {
    //     //uprintf("NO TRANSPORT CONNECTED\n");
    //     return;
    // }

//     if (is_keyboard_master()) {
//         // Interact with slave every 500ms
//         static uint32_t last_sync = 0;
//         if (timer_elapsed32(last_sync) >500) {
//             // uprintf("0.5 segundos\n"); // this will now be 11, as the slave adds 5
//             last_sync = timer_read32();

//             if (transaction_rpc_send(KB_MODE_SYNC, sizeof(bool), &render_indicators)) {
//                 last_sync = timer_read32();
//             } else {
// #if defined(CONSOLE_ENABLE)
//                 dprint("Failed to perform rpc call\n");
// #endif
//             }
//         }
//     }
//}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

#if defined(CONSOLE_ENABLE)
    uprintf("SA PULSAO O DESPULSAO UNA TECLA: %2u\n", keycode);
#endif
    switch (keycode)
    {
        case PB_1:
            // Play a tone when enter is pressed
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PERSONALIZED_KC_COLORS);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }

            return true; // Let QMK send the enter press/release events
            break;
        case PB_2:
            // Play a tone when enter is pressed
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PERSONALIZED_KC_COLORS_BREATHING);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_3:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_PIXEL_FLOW);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_4:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_5:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_6:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_PINWHEELS);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_7:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTICROSS);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_8:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_9:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_JELLYBEAN_RAINDROPS);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_10:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_PIXEL_FRACTAL);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_11:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_12:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_DIGITAL_RAIN);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_13:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_MULTISPLASH);
                HSV hsv = {HSV_RED};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_14:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
                HSV hsv = {HSV_BLUE};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        case PB_15:
            if (record->event.pressed)
            {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
                HSV hsv = {HSV_BLUE};
                rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, rgb_matrix_config.hsv.v);
            }
            break;
        default:
            return true; // Process all other keycodes normally
    }

    return true;  // Process all other keycodes normally
}


 bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
     uint8_t current_layer = get_highest_layer(layer_state);

     PERSONALIZED_KC_COLORS_set_active_layer(current_layer);

#if defined(CONSOLE_ENABLE)
        bool caps_lock = host_keyboard_led_state().caps_lock;

        static uint32_t last_sync_indicators = 0;
        if (timer_elapsed32(last_sync_indicators) >5000) {
            last_sync_indicators = timer_read32();
            uprintf("CURRENT LAYER: %2u \n", current_layer);
            uprintf("CAPS LOCK: %2u \n", caps_lock);
        }
#endif

     return false;
}


bool encoder_update_user(uint8_t index, bool clockwise)
{
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0)
    {
        // Right and Left arrow
        if (clockwise)
        {
            tap_code(KC_RIGHT);
        } else
        {

            tap_code(KC_LEFT);
        }
    } else if (index == 1)
    {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return false;
}
