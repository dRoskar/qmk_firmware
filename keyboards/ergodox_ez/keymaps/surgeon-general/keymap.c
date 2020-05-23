#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ALTF4_MACRO,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
  ST_MACRO_4,
  ST_MACRO_5,
  ST_MACRO_6,
  STATS_ADMIN_MACRO,
  INTELLIJ_FIND_FILE_MACRO,
  SUPER_ALT_TAB,
  JUNK_MAIL_MACRO,
  PERSONAL_MAIL_MACRO,
  CPY_ALL_MACRO,
  CUT_ALL_MACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    LCTL(SI_CEDL),  KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 LCTL(KC_X),     KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           LCTL(LSFT(KC_Y)),
    KC_TRANSPARENT, KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           KC_TRANSPARENT,                                 LCTL(KC_C),     KC_J,           KC_L,           KC_U,           KC_Z,           SI_MINS,        LCTL(KC_Y),
    KC_TAB,         LCTL_T(KC_A),   LALT_T(KC_R),   KC_S,           LSFT_T(KC_T),   KC_G,                                                                           KC_K,           RSFT_T(KC_N),   KC_E,           LALT_T(KC_I),   RCTL_T(KC_O),   KC_DELETE,
    SUPER_ALT_TAB,  KC_Y,           KC_X,           KC_C,           KC_D,           KC_V,           KC_TRANSPARENT,                                 LCTL(KC_V),     KC_M,           KC_H,           KC_COMMA,       KC_DOT,         SI_QUOT,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_ESCAPE,      MO(4),          KC_SPACE,                                                                                                       KC_BSPACE,      MO(3),          KC_LGUI,        KC_TRANSPARENT, TG(6),
                                                                                                    KC_TRANSPARENT, KC_PGUP,        LCTL(KC_PSCREEN),KC_TRANSPARENT,
                                                                                                                    KC_PGDOWN,      KC_TRANSPARENT,
                                                                                    MO(1),          LT(5,KC_HOME),  KC_TRANSPARENT, KC_TRANSPARENT, KC_END,         LT(2,KC_ENTER)
  ),
  [1] = LAYOUT_ergodox_pretty(
    SI_TILD,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, SI_HASH,        SI_AMPR,        SI_LCBR,        SI_RCBR,        SI_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, SI_DLR,         SI_COLN,        KC_UP,          SI_SCLN,        SI_PLUS,        KC_F12,
    KC_TRANSPARENT, SI_EXLM,        SI_AT,          SI_LPRN,        SI_RPRN,        SI_LABK,                                                                        SI_EQL,         KC_LEFT,        KC_DOWN,        KC_RIGHT,       SI_QUES,        KC_TRANSPARENT,
    KC_LSHIFT,      SI_SLSH,        SI_BSLS,        SI_LBRC,        SI_RBRC,        SI_RABK,        ALTF4_MACRO,                                     KC_TRANSPARENT, SI_EURO,        SI_PERC,        SI_CIRC,        SI_ASTR,        SI_DQUO,        KC_TRANSPARENT,
    KC_LCTRL,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, SI_DEG,         SI_MUL,         SI_DIV,         KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_ergodox_pretty(
    WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, LSFT(LCTL(KC_T)), KC_MS_WH_UP,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_AUDIO_VOL_UP,KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_MS_WH_LEFT,    KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_AUDIO_VOL_DOWN,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                               KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK,      KC_TRANSPARENT, KC_WWW_FORWARD, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN2,     KC_MS_BTN3,     KC_MS_BTN1,                                                                                                     KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, SI_SCAR,        KC_LSHIFT,      KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_RSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, SI_ZCAR,        KC_TRANSPARENT, SI_CCAR,        SI_DSTR,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_3,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_1,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_4,     KC_TRANSPARENT, ST_MACRO_5,     KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_2,     KC_TRANSPARENT, SI_SS,          KC_LSHIFT,      KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_RSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_6,     KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, JUNK_MAIL_MACRO,   PERSONAL_MAIL_MACRO, KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 CUT_ALL_MACRO,  KC_TRANSPARENT, KC_TRANSPARENT,       KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, STATS_ADMIN_MACRO, KC_TRANSPARENT,      KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 CPY_ALL_MACRO,  LSFT(KC_F11),   LSFT(LCTL(KC_F)),     LALT(KC_UP),    INTELLIJ_FIND_FILE_MACRO, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      LALT(RCTL(KC_A)),  KC_TRANSPARENT, KC_TRANSPARENT,                                                                 LCTL(KC_F11),   LALT(LCTL(KC_LEFT)),  LALT(KC_DOWN),  LALT(LCTL(KC_RIGHT)),     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, LALT(KC_F8),    LCTL(KC_KP_SLASH),    KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      KC_TRANSPARENT,    KC_TRANSPARENT,                                                                                                 KC_F8,                KC_F7,          LSFT(KC_F8),              KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                        LALT(LCTL(KC_C)),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                        KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F9
  ),
  [6] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_M,           KC_ESCAPE,      KC_Q,           KC_W,           KC_E,           KC_R,           KC_I,                                           KC_J,           KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSHIFT,      KC_A,           KC_S,           KC_D,           KC_F,                                                                           KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LCTRL,       KC_Z,           KC_X,           KC_C,           KC_V,           KC_L,                                           KC_K,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_MS_BTN1,     KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_SPACE,       KC_I,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_ENTER
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALTF4_MACRO:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_DELAY(100) SS_LSFT(SS_TAP(X_A)));

    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_DELAY(100) SS_TAP(X_A));

    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_DELAY(100) SS_LSFT(SS_TAP(X_U)));

    }
    break;
    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_DELAY(100) SS_TAP(X_U));

    }
    break;
    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_DELAY(100) SS_LSFT(SS_TAP(X_O)));

    }
    break;
    case ST_MACRO_6:
    if (record->event.pressed) {
      SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_DELAY(100) SS_TAP(X_O));

    }
    break;
    case STATS_ADMIN_MACRO:
    if (record->event.pressed) {
      SEND_STRING("***" SS_RALT(SS_TAP(X_V)) "***"SS_TAP(X_TAB)"***");
    }
    break;
    case INTELLIJ_FIND_FILE_MACRO:
    if (record->event.pressed) {
      register_code(KC_LSFT);
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      unregister_code(KC_LSFT);
    }
    break;
    case SUPER_ALT_TAB:
    if (record->event.pressed) {
      if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
    break;
    case JUNK_MAIL_MACRO:
    if (record->event.pressed) {
      SEND_STRING("***"SS_RALT(SS_TAP(X_V))"gmail.com");
    }
    break;
    case PERSONAL_MAIL_MACRO:
  	if (record->event.pressed) {
      SEND_STRING("***"SS_RALT(SS_TAP(X_V))"gmail.com");
    }
    break;
    case CPY_ALL_MACRO:
  	if (record->event.pressed) {
      SEND_STRING(SS_LCTL("ac"));
    }
    break;
    case CUT_ALL_MACRO:
  	if (record->event.pressed) {
      SEND_STRING(SS_LCTL("ax"));
    }
    break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 650) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};
