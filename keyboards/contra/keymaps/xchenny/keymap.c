#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum contra_layers {
  _QWERTY,
  _NUMB,
  _FUNC,
};

enum contra_keycodes {
  M_TEST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-------------------------------------------------------------------------------------------------.
   * | Tab / Numb  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \          |
   * |-------------+------+------+------+------+-------------+------+------+------+------+-------------|
   * | Esc / Ctrl  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '          |
   * |-------------+------+------+------+------+------|------+------+------+------+------+-------------|
   * | Shift / (   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   Sft / )   |
   * |-------------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl        |GUI   | Alt  |   |  Del |Bspc  |Space |Enter |  [   |  ]   |  -   |  =          |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_ortho_4x12(
    LT(_NUMB, KC_TAB),   KC_Q,    KC_W,    KC_E,       KC_R,      KC_T,      KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    LCTL_T(KC_ESC),      KC_A,    KC_S,    KC_D,       KC_F,      KC_G,      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSPO,             KC_Z,    KC_X,    KC_C,       KC_V,      KC_B,      KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
    LCTL_T(KC_GRV),      KC_LGUI, KC_LALT, MO(_FUNC),  KC_DEL,    KC_BSPC,   KC_SPC, KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
  ),

  /* Func
   * ,-----------------------------------------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Play |      | Prev | Vol- | Vol+ | Next |
   * `-----------------------------------------------------------------------------------'
   */
  [_FUNC] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,      KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,     KC_F5,      KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LSFT, KC_F7,   KC_F8,   KC_F9,    KC_F10,    KC_F11,     KC_F12,  KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE,
    KC_SLEP, _______, _______, _______,  _______,   _______,    KC_MUTE, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),

  [_NUMB] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, KC_BSPC,
    _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______,
    _______, _______, _______, _______, _______, KC_BSPC, _______, KC_0,    KC_0,    _______, _______, M_TEST
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_TEST:
      if (record->event.pressed) {
        SEND_STRING("HI MOM");
      }
      return false;
      break;
  }
  return true;
}
