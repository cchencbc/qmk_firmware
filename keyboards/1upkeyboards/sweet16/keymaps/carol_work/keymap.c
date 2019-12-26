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
    A_TEXT,
    A_HATCH,
    A_CHSPACE,

    R_BOX,
    R_TEXT,
    R_CREATESIM,
    R_HIDE,
    R_MIRROR,
    R_COPY,
    R_ALIGN,
    R_MOVE,
    R_ROTATE,
    R_TRIM,
    R_VISIBILITY,
    R_DETAILLINE,
    R_SCALE,
    R_DIMENSION
};

// Tap Dance Declarations
enum { 
    TD_SNGL_DBL_QUOTE = 0,
    TD_ENTER_LAYERAC,
    TD_PLUS_MINUS,
    TD_AST_SLSH,
    TD_EQUAL_QUESTION,
    TD_ENTER_LAYERNUM,
    TD_7_X,
    TD_LINE_PL,
    TD_REC_CIRCLE,
    TD_TEXT_DIM,
    TD_HATCH_CHSPACE,
    TD_DOT_REVIT
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for single quote, and twice for double quote
    [TD_SNGL_DBL_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
    [TD_ENTER_LAYERAC] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ENT, _AUTOCAD),
    [TD_PLUS_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS,KC_MINS),
    [TD_AST_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_ASTR,KC_SLSH),
    [TD_EQUAL_QUESTION] = ACTION_TAP_DANCE_DOUBLE(KC_KP_EQUAL,KC_QUESTION),
    [TD_ENTER_LAYERNUM] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ENT, _NUMPAD),
    [TD_7_X] = ACTION_TAP_DANCE_DOUBLE(KC_7,KC_X),
    [TD_LINE_PL] = ACTION_TAP_DANCE_DOUBLE(A_LINE,A_POLYLINE),
    [TD_REC_CIRCLE] = ACTION_TAP_DANCE_DOUBLE(A_RECTANGLE,A_CIRCLE),
    [TD_TEXT_DIM] = ACTION_TAP_DANCE_DOUBLE(A_TEXT,A_DIMENSION),
    [TD_HATCH_CHSPACE] = ACTION_TAP_DANCE_DOUBLE(A_HATCH,A_CHSPACE),
    [TD_DOT_REVIT] = ACTION_TAP_DANCE_LAYER_MOVE(KC_DOT, _REVIT)
};

uint16_t key_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT_ortho_4x4(
        TD(TD_7_X), KC_8, KC_9, TD(TD_SNGL_DBL_QUOTE),
        KC_4, KC_5, KC_6, TD(TD_AST_SLSH),
        KC_1, KC_2, KC_3, TD(TD_PLUS_MINUS),
        TD(TD_EQUAL_QUESTION), KC_0, TD(TD_DOT_REVIT), TD(TD_ENTER_LAYERAC)),

    [_AUTOCAD] = LAYOUT_ortho_4x4(
        KC_ESCAPE, A_POLYLINE, KC_9, KC_DELETE,
        TD(TD_LINE_PL), TD(TD_REC_CIRCLE), TD(TD_TEXT_DIM), TD(TD_HATCH_CHSPACE),
        A_ROTATE, A_MOVE, A_COPY, A_FILLET,
        A_TRIM, A_EXT, TD(TD_SNGL_DBL_QUOTE), TD(TD_ENTER_LAYERNUM)),
                                                              
    [_REVIT]   = LAYOUT_ortho_4x4(
        KC_ESCAPE, R_BOX, R_TEXT, KC_DELETE,
        R_CREATESIM, R_HIDE, R_MIRROR, R_COPY,
        R_ALIGN, R_MOVE, R_ROTATE, R_TRIM,
        R_VISIBILITY, R_DETAILLINE, R_DETAILLINE, TD(TD_ENTER_LAYERNUM))
};

//missing scale for Revit
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
        case A_TEXT:
            if (record->event.pressed) {
                SEND_STRING(ATEXT_STR);
            }
            return false;
            break;
        case A_HATCH:
            if (record->event.pressed) {
                SEND_STRING(AHATCH_STR);
            }
            return false;
            break;
        case A_CHSPACE:
            if (record->event.pressed) {
                SEND_STRING(ACHSPACE_STR);
            }
            return false;
            break;
        case A_POLYLINE:
            if (record->event.pressed) {
                SEND_STRING(APOLYLINE_STR);
            }
            return false;
            break;
         case R_CREATESIM:
            if (record->event.pressed) {
                SEND_STRING(RCREATE_SIM_STR);
            }
            return false;
            break;
        case R_TRIM:
            if (record->event.pressed) {
                SEND_STRING(RTRIM_STR);
            }
            return false;
            break;
        case R_MIRROR:
            if (record->event.pressed) {
                SEND_STRING(RMIRROR_STR);
            }
            return false;
            break;
        case R_ROTATE:
            if (record->event.pressed) {
                SEND_STRING(RROTATE_STR);
            }
            return false;
            break;
        case R_COPY:
            if (record->event.pressed) {
                SEND_STRING(RCOPY_STR);
            }
            return false;
            break;
        case R_DETAILLINE:
            if (record->event.pressed) {
                SEND_STRING(RDETAILLINE_STR);
            }
            return false;
            break;
        case R_BOX:
            if (record->event.pressed) {
                SEND_STRING(RBOX_STR);
            }
            return false;
            break;
        case R_TEXT:
            if (record->event.pressed) {
                SEND_STRING(RTEXT_STR);
            }
            return false;
            break;
        case R_HIDE:
            if (record->event.pressed) {
                SEND_STRING(RHIDE_STR);
            }
            return false;
            break;
        case R_SCALE:
            if (record->event.pressed) {
                SEND_STRING(RSCALE_STR);
            }
            return false;
            break;
        case R_MOVE:
            if (record->event.pressed) {
                SEND_STRING(RMOVE_STR);
            }
            return false;
            break;
        case R_DIMENSION:
            if (record->event.pressed) {
                SEND_STRING(RDIMENSION_STR);
            }
            return false;
            break;
        case R_ALIGN:
            if (record->event.pressed) {
                SEND_STRING(RALIGN_STR);
            }
            return false;
            break;
        case R_VISIBILITY:
            if (record->event.pressed) {
                SEND_STRING(RVISIBILITY_STR);
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
