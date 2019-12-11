#include QMK_KEYBOARD_H
#include "commands.h"

#define _NUMPAD 0
#define _AUTOCAD 1
#define _REVIT 2

enum custom_keycodes {
    // autocad macros
    A_TRIM = SAFE_RANGE,
    A_EXT,
    A_MIRROR,
    A_ROTATE,
    A_MOVE,
    A_COPY,
    A_FILLET,
    A_OFFSET,
    A_LINE,
    A_DIMENSION,
    A_RECTANGLE,
    A_CIRCLE,
    A_POLYLINE,

    // revit macros
    // #define RCREATE_SIM_STR "cs"
    // #define RTRIM_STR "tr"
    // #define RMIRROR_STR "mm"
    // #define RROTATE_STR "ro"
    // #define RCOPY_STR "cc"
    // #define RDETAILLINE_STR "dl"
};

// Tap Dance Declarations
enum { TD_SNGL_DBL_QUOTE = 0 };

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for single quote, and twice for double quote
    [TD_SNGL_DBL_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE)};

uint16_t key_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT_ortho_4x4(
        KC_7, KC_8, KC_9, TD(TD_SNGL_DBL_QUOTE),
        KC_4, KC_5, KC_6, KC_SLSH,
        KC_1, KC_2, KC_3, KC_MINS,
        KC_0, KC_ENT, KC_DOT, TO(_AUTOCAD)),

    [_AUTOCAD] = LAYOUT_ortho_4x4(
        A_CIRCLE, A_POLYLINE, KC_9, TD(TD_SNGL_DBL_QUOTE),
        A_OFFSET, A_LINE, A_DIMENSION, A_RECTANGLE,
        A_ROTATE, A_MOVE, A_COPY, A_FILLET,
        A_TRIM, A_EXT, A_MIRROR, TO(_REVIT)),
                                                              
    [_REVIT]   = LAYOUT_ortho_4x4(
        KC_7, KC_8, KC_9, TD(TD_SNGL_DBL_QUOTE),
        KC_4, KC_5, KC_6, KC_SLSH,
        KC_1, KC_2, KC_3, KC_MINS,
        KC_0, KC_ENT, KC_DOT, TO(_NUMPAD))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_TRIM:
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LCTRL);
            } else {
                unregister_code(KC_LCTRL);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    SEND_STRING(ATRIM_STR);
                }
            } 
            break;
            // if (record->event.pressed) {
            //     SEND_STRING(ATRIM_STR);
            // }
            // return false;
            // break;
        case A_EXT:
            if (record->event.pressed) {
                SEND_STRING(AEXT_STR);
            }
            return false;
            break;
        case A_MIRROR:
            if (record->event.pressed) {
                SEND_STRING(AMIRROR_STR);
            }
            return false;
            break;
        case A_ROTATE:
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_LSFT);
                break;
            } else {
                unregister_code(KC_LSFT);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    SEND_STRING(AROTATE_STR);
                }
            } 
            break;
            // if (record->event.pressed) {
            //     SEND_STRING(AROTATE_STR);
            // }
            // return false;
            // break;
        case A_MOVE:
            if (record->event.pressed) {
                SEND_STRING(AMOVE_STR);
            }
            return false;
            break;
        case A_COPY:
            if (record->event.pressed) {
                SEND_STRING(ACOPY_STR);
            }
            return false;
            break;
        case A_FILLET:
            if (record->event.pressed) {
                SEND_STRING(AFILLET_STR);
            }
            return false;
            break;
        case A_OFFSET:
            if (record->event.pressed) {
                SEND_STRING(AOFFSET_STR);
            }
            return false;
            break;
        case A_LINE:
            if (record->event.pressed) {
                SEND_STRING(ALINE_STR);
            }
            return false;
            break;
        case A_DIMENSION:
            if (record->event.pressed) {
                SEND_STRING(ADIMENSION_STR);
            }
            return false;
            break;
        case A_RECTANGLE:
            if (record->event.pressed) {
                SEND_STRING(ARECTANGLE_STR);
            }
            return false;
            break;
        case A_CIRCLE:
            if (record->event.pressed) {
                SEND_STRING(ACIRCLE_STR);
            }
            return false;
            break;
        case A_POLYLINE:
            if (record->event.pressed) {
                SEND_STRING(APOLYLINE_STR);
            }
            return false;
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
#    include "encoder.h"
void encoder_update_user(int8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
#endif
