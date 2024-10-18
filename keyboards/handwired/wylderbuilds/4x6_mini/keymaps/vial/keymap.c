#include QMK_KEYBOARD_H
#include "4x6_mini.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum wyld_keycodes {
    WYLD_AUTO_MS_TOG = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_4x6(
        KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,                         KC_Y, KC_U, KC_I,   KC_O,   KC_P,    KC_MINS,
        KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G,  KC_MUTE,               KC_H, KC_J, KC_K,   KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                         KC_N, KC_M, KC_COMM,KC_DOT ,KC_SLSH, KC_BSLS,
                       KC_LCTL, KC_LALT,                                                 KC_RCTL,KC_RALT,
                                RAISE, KC_SPC, KC_BSPC,        KC_DEL, KC_ENT, LOWER,
                                        KC_TAB, KC_HOME,       KC_RGUI, KC_RALT

        ),

    [_LOWER] = LAYOUT_4x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,               KC_CIRC,KC_P7,KC_P8,KC_P9 ,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC, KC_HOME,     KC_RBRC, KC_P4 , KC_P5 , KC_P6 ,KC_PLUS, KC_ASTR,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,               KC_RPRN, KC_P1 , KC_P2 , KC_P3 ,KC_MINS,KC_EQL,
                        _______,_______,                                                KC_P0 , KC_DOT,
                                 _______,_______,_______,      _______,_______,_______,
                                          _______,_______,     _______, QK_BOOT
        ),

    [_RAISE] = LAYOUT_4x6(
        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,               KC_F6, KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        _______,_______,_______,_______,_______,KC_LBRC, KC_MUTE,      KC_RBRC,_______,KC_NUM,KC_INS ,KC_SCRL,KC_MUTE,
        _______,KC_LEFT,KC_UP,KC_DOWN,KC_RGHT,KC_LPRN,                 KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,KC_VOLD,KC_VOLU,
                        _______,_______,                                               _______,_______,
                                   _______,_______,_______,     _______,_______,_______,
                                           QK_BOOT,_______,     _______,_______
        )
//    [_MOUSE] = LAYOUT_4x6(
//        _______,_______,_______,_______,_______,_______,               _______,_______,_______,_______,_______,_______,
//        _______,_______,KC_BTN2,KC_BTN3,KC_BTN1,_______, KC_MUTE,      _______,KC_BTN1,KC_BTN3,KC_BTN2,_______,_______,
//        _______,_______,_______,_______,_______,_______,               _______,SNIPING,DRGSCRL,_______,_______,_______,
//                        _______,_______,                                               _______,_______,
//                                   _______,KC_BTN1,KC_BTN3,      _______,_______,_______,
//                                            SNIPING,DRGSCRL,     _______, _______
//        )
};

//void pointing_device_init_user(void) {
//    //    set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
//    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
//    set_auto_mouse_enable(false);    // disabled by default
//}

//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//    switch (keycode) {
//        case WYLD_AUTO_MS_TOG:
//            if (record->event.pressed) {
//                set_auto_mouse_enable(!get_auto_mouse_enable());
//            }
//            return false; // Skip all further processing of this key
//        default:
//            return true; // Process all other keycodes normally
//    }
//}


//    rgblight_enable();

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
#else
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
    debug_mouse=false;
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_layers = my_rgb_layers;
#endif
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] =  { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_LOWER] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_RAISE] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) }
//    [_MOUSE] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) }
//};
//    [_QWERTY] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
//    [_LOWER] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
//    [_RAISE] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
//    [_MOUSE] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}


static char layer_names[5][8] = {
            " BASE\n",
            "LOWER\n",
            "RAISE\n",
            "MOUSE\n",
            " XTRA\n"
            };

bool oled_task_user(void) {
    char* layer_name = layer_names[get_highest_layer(layer_state)];
//    char* mode = get_mouse_mode_string();

//    if (is_keyboard_left()) {
        //        oled_write_P(PSTR("Layer\n"), false);
 oled_set_cursor(0, 3);
        oled_write_P(PSTR(layer_name), false);

        oled_set_cursor(2, 6);
        oled_write_P(PSTR("WPM "), false);
        oled_set_cursor(2, 7);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);
        // Host Keyboard LED Status

        oled_set_cursor(0, 9);
        led_t led_state = host_keyboard_led_state();

        oled_write_P(led_state.num_lock ? PSTR("NUMLK \n") : PSTR("    \n"), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAPLK \n") : PSTR("    \n"), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCRLK \n") : PSTR("    \n"), false);
//    }

    return false;
}
#endif




