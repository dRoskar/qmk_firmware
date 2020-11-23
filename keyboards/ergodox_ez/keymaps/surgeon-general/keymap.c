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
static uint8_t saved_mods = 0;

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  AT_ALT = 0,
  F5_CLEAR_CACHE,
  MEOW
};

int cur_dance (qk_tap_dance_state_t *state);

//for the at_alt tap dance. Put it here so it can be used in any keymap
void at_alt_finished (qk_tap_dance_state_t *state, void *user_data);
void at_alt_reset (qk_tap_dance_state_t *state, void *user_data);

//for the f5 tap dance. Put it here so it can be used in any keymap
void f5_finished (qk_tap_dance_state_t *state, void *user_data);
void f5_reset (qk_tap_dance_state_t *state, void *user_data);


enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ALTF4_MACRO,
  GER_A_MACRO,
  GER_U_MACRO,
  GER_O_MACRO,
  STATS_ADMIN_MACRO,
  INTELLIJ_FIND_FILE_MACRO,
  SUPER_ALT_TAB,
  JUNK_MAIL_MACRO,
  PERSONAL_MAIL_MACRO,
  CPY_ALL_MACRO,
  CUT_ALL_MACRO,
  REPLACE_PASTE_MACRO,
  REAPER_INSERT_MARKER_MACRO,
  REAPER_INSERT_REGION_MACRO,
  REAPER_ACTIONS_MENU_MACRO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty( /*Main*/
    LCTL(SI_CEDL),  KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           TD(MEOW),                                       LCTL(KC_X),     KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           LCTL(LSFT(KC_Y)),
    KC_TRANSPARENT, KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           KC_TRANSPARENT,                                 LCTL(KC_C),     KC_J,           KC_L,           KC_U,           KC_Z,           SI_MINS,        LCTL(KC_Y),
    KC_TAB,         LCTL_T(KC_A),   LALT_T(KC_R),   KC_S,           LSFT_T(KC_T),   KC_G,                                                                           KC_K,           RSFT_T(KC_N),   KC_E,           LALT_T(KC_I),   RCTL_T(KC_O),   KC_DELETE,
    SUPER_ALT_TAB,  KC_Y,           KC_X,           KC_C,           KC_D,           KC_V,           KC_TRANSPARENT,                                 LCTL(KC_V),     KC_M,           KC_H,           KC_COMMA,       KC_DOT,         SI_QUOT,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_ESCAPE,      MO(4),          KC_SPACE,                                                                                                       KC_BSPACE,      MO(3),          KC_LGUI,        KC_TRANSPARENT, TG(6),
                                                                                                    KC_TRANSPARENT, KC_PGUP,        LCTL(KC_PSCREEN),KC_TRANSPARENT,
                                                                                                                    KC_PGDOWN,      KC_TRANSPARENT,
                                                                                    MO(1),          LT(5,KC_END),  KC_TRANSPARENT, KC_TRANSPARENT, KC_HOME,         LT(2,KC_ENTER)
  ),
  [1] = LAYOUT_ergodox_pretty( /*Symbols*/
    SI_TILD,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          TD(F5_CLEAR_CACHE), KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    KC_TRANSPARENT, SI_HASH,        SI_AMPR,        SI_LCBR,        SI_RCBR,        SI_PIPE,            KC_TRANSPARENT,                                 KC_TRANSPARENT, SI_DLR,         SI_COLN,        KC_UP,          SI_SCLN,        SI_PLUS,        KC_F12,
    KC_TRANSPARENT, KC_LCPO,        TD(AT_ALT),     SI_LPRN,        KC_LSPO,        SI_LABK,                                                                            SI_EQL,         KC_LEFT,        KC_DOWN,        KC_RIGHT,       SI_QUES,        KC_TRANSPARENT,
    KC_TRANSPARENT, SI_SLSH,        SI_BSLS,        SI_LBRC,        SI_RBRC,        SI_RABK,            KC_TRANSPARENT,                                 KC_TRANSPARENT, SI_EURO,        SI_PERC,        SI_CIRC,        SI_ASTR,        SI_DQUO,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                     KC_TRANSPARENT, SI_DEG,         SI_MUL,         SI_DIV,         KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_ergodox_pretty( /*Mouse and web*/
    WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 MEH(KC_D), KC_TRANSPARENT, LSFT(LCTL(KC_T)), KC_MS_WH_UP,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_AUDIO_VOL_UP,KC_LSFT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,                                                                        KC_TRANSPARENT, KC_MS_WH_LEFT,    KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_AUDIO_VOL_DOWN,KC_LCTL, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                      MEH(KC_V), KC_TRANSPARENT, KC_WWW_BACK,      KC_TRANSPARENT, KC_WWW_FORWARD, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN2,     KC_MS_BTN3,     KC_MS_BTN1,                                                                                                     KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty( /*SLO*/
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, SI_SCAR,        KC_LSHIFT,      KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_RSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, SI_ZCAR,        KC_TRANSPARENT, SI_CCAR,        SI_DSTR,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_ergodox_pretty( /*GER*/
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, GER_U_MACRO,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, GER_A_MACRO,     KC_TRANSPARENT, SI_SS,         KC_LSHIFT,      KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_RSHIFT,     KC_TRANSPARENT,  KC_TRANSPARENT, GER_O_MACRO,    KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_ergodox_pretty( /*Macro/Intellij*/
    KC_TRANSPARENT, JUNK_MAIL_MACRO,   PERSONAL_MAIL_MACRO, KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT, TO(7),                                          CUT_ALL_MACRO,       KC_TRANSPARENT, KC_TRANSPARENT,       KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, STATS_ADMIN_MACRO, KC_TRANSPARENT,      KC_TRANSPARENT,    KC_TRANSPARENT, MEH(KC_E), KC_TRANSPARENT,                                 CPY_ALL_MACRO,       LSFT(KC_F11),   LSFT(LCTL(KC_F)),     LALT(KC_UP),    INTELLIJ_FIND_FILE_MACRO, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      MEH(KC_S),         KC_TRANSPARENT, KC_TRANSPARENT,                                                                      LCTL(KC_F11),   LALT(LCTL(KC_LEFT)),  LALT(KC_DOWN),  LALT(LCTL(KC_RIGHT)),     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT, ALTF4_MACRO,                                    REPLACE_PASTE_MACRO, LALT(KC_F8),    LCTL(KC_KP_SLASH),    LALT(KC_INS), KC_TRANSPARENT,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      KC_TRANSPARENT,    KC_TRANSPARENT,                                                                                                 KC_F8,                KC_F7,          LSFT(KC_F8),              KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                        MEH(KC_C),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                        KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F9
  ),
  [6] = LAYOUT_ergodox_pretty( /*Game*/
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_ESCAPE,
    KC_M,           KC_ESCAPE,      KC_Q,           KC_UP,           KC_E,           KC_R,           KC_I,                                           KC_J,           KC_TRANSPARENT, KC_E,           KC_W,           KC_Q,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSHIFT,      KC_LEFT,        KC_DOWN,           KC_RIGHT,           KC_F,                                                                           KC_F,           KC_A,           KC_S,           KC_D,           KC_LSHIFT,      KC_TAB,
    KC_TRANSPARENT, KC_LCTRL,       KC_Z,           KC_X,           KC_C,           KC_V,           KC_L,                                           KC_K,           KC_L,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LCTRL,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_SPACE,       KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    MEH(KC_K),       MEH(KC_J),           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_END
  ),
  [7] = LAYOUT_ergodox_pretty( /*Reaper*/
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(0),                                          REAPER_ACTIONS_MENU_MACRO, LCTL(KC_T),       REAPER_INSERT_MARKER_MACRO, REAPER_INSERT_REGION_MACRO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LCTL(KC_UP),    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT,            MEH(KC_T),        KC_R,                       LALT(KC_S),                 KC_TRANSPARENT, SI_DSTR,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, LCTL(KC_LEFT),  LCTL(KC_DOWN),  LCTL(KC_RIGHT), KC_TRANSPARENT,                                                                            LCTL(LSFT(KC_G)), KC_LSFT,                    KC_S,                       KC_LALT,        KC_LCTL,        KC_TRANSPARENT,
    KC_TRANSPARENT, SI_ZCAR,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT,            KC_TRANSPARENT,   KC_TRANSPARENT,             KC_TRANSPARENT,             KC_TRANSPARENT, KC_LCTL,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                              KC_SPACE,                   KC_TRANSPARENT,             KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LCTL(KC_R), KC_ENTER
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALTF4_MACRO:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));

    }
    break;
    case GER_A_MACRO:
    if (record->event.pressed) {
      if (get_mods() & MOD_MASK_SHIFT) {
        saved_mods = get_mods();
        clear_mods();
        SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_LSFT(SS_TAP(X_A)));
        set_mods(saved_mods);
      } else {
        SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_TAP(X_A));
      }
    }
    break;
    case GER_U_MACRO:
    if (record->event.pressed) {
      if (get_mods() & MOD_MASK_SHIFT) {
        saved_mods = get_mods();
        clear_mods();
        SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_LSFT(SS_TAP(X_U)));
        set_mods(saved_mods);
      } else {
        SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_TAP(X_U));
      }
    }
    break;
    case GER_O_MACRO:
    if (record->event.pressed) {
      if (get_mods() & MOD_MASK_SHIFT) {
        saved_mods = get_mods();
        clear_mods();
        SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_LSFT(SS_TAP(X_O)));
        set_mods(saved_mods);
      } else {
        SEND_STRING(SS_RALT(SS_TAP(X_MINUS)) SS_TAP(X_O));
      }
    }
    break;
    case STATS_ADMIN_MACRO:
    if (record->event.pressed) {
      SEND_STRING("la.droskar" SS_RALT(SS_TAP(X_V)) "statsllc.onmicrosoft.com"SS_TAP(X_TAB)"Kadu9491"SS_TAP(X_ENTER));
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
      SEND_STRING("mastuh8"SS_RALT(SS_TAP(X_V))"gmail.com");
    }
    break;
    case PERSONAL_MAIL_MACRO:
  	if (record->event.pressed) {
      SEND_STRING("damjan.roskar.s"SS_RALT(SS_TAP(X_V))"gmail.com");
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
    case REPLACE_PASTE_MACRO:
  	if (record->event.pressed) {
      SEND_STRING(SS_LCTL("av"));
    }
    break;
    case REAPER_INSERT_MARKER_MACRO:
  	if (record->event.pressed) {
      SEND_STRING(SS_LSFT("m"));
    } else {
      layer_off(7);
    } 
    break;
    case REAPER_INSERT_REGION_MACRO:
  	if (record->event.pressed) {
      SEND_STRING(SS_LSFT("r"));
    } else {
      layer_off(7);
    }
    break;
    case REAPER_ACTIONS_MENU_MACRO:
  	if (record->event.pressed) {
      SEND_STRING(SS_LSFT("-")); // ?
    } else {
      layer_off(7);
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
      ergodox_right_led_2_on();
      break;
    default:
      break;
  }
  return state;
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

// ------------------------- AT ALT TAP DANCE ----------------------------

//instanalize an instance of 'tap' for the 'at_alt' tap dance.
static tap at_alt_tap_state = {
  .is_press_action = true,
  .state = 0
};

void at_alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  at_alt_tap_state.state = cur_dance(state);
  switch (at_alt_tap_state.state) {
    case SINGLE_TAP: register_code(KC_RALT); register_code(KC_V); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: register_code(KC_RALT); register_code(KC_V); unregister_code(KC_V); unregister_code(KC_RALT); register_code(KC_RALT); register_code(KC_V); break;
    case DOUBLE_HOLD: register_code(KC_RALT); register_code(KC_V); unregister_code(KC_V); unregister_code(KC_RALT); register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_RALT); register_code(KC_V); unregister_code(KC_V); unregister_code(KC_RALT); register_code(KC_RALT); register_code(KC_V); 
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void at_alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (at_alt_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_V); unregister_code(KC_RALT); break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_V); unregister_code(KC_RALT); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_V); unregister_code(KC_RALT);
  }
  at_alt_tap_state.state = 0;
}

// ------------------------- F5 / CLEAR CACHE TAP DANCE ----------------------------

//instanalize an instance of 'tap' for the 'f5' tap dance.
static tap f5_tap_state = {
  .is_press_action = true,
  .state = 0
};

void f5_finished (qk_tap_dance_state_t *state, void *user_data) {
  f5_tap_state.state = cur_dance(state);
  switch (f5_tap_state.state) {
    case SINGLE_TAP: register_code(KC_F5); break;
    case SINGLE_HOLD: register_code(KC_F5); break;
    case DOUBLE_TAP: register_code(KC_LCTL); register_code(KC_F5); break;
    case DOUBLE_HOLD: register_code(KC_F5); unregister_code(KC_F5); register_code(KC_F5); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_F5); unregister_code(KC_F5); register_code(KC_F5);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void f5_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (f5_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_F5); break;
    case SINGLE_HOLD: unregister_code(KC_F5); break;
    case DOUBLE_TAP: unregister_code(KC_F5); unregister_code(KC_LCTL); break;
    case DOUBLE_HOLD: unregister_code(KC_F5);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_F5);
  }
  f5_tap_state.state = 0;
}

// ------------------------- MEOW TAP DANCE ----------------------------

//instanalize an instance of 'tap' for the 'f5' tap dance.
static tap meow_tap_state = {
  .is_press_action = true,
  .state = 0
};

void meow (qk_tap_dance_state_t *state, void *user_data) {
  meow_tap_state.state = cur_dance(state);
  if (state->count >= 9) {
      SEND_STRING(SS_LCTL(SS_RALT(SS_LSFT(SS_TAP(X_N)))));
      ergodox_right_led_1_on();
      wait_ms(15);
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_1_off();
      wait_ms(15);
      ergodox_right_led_3_off();
      ergodox_right_led_2_on();
      wait_ms(15);
      ergodox_right_led_1_on();
      wait_ms(15);
      ergodox_right_led_1_off();
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_2_off();
      wait_ms(15);
      ergodox_right_led_2_on();
      ergodox_right_led_1_on();
      ergodox_right_led_3_off();
      wait_ms(15);
      ergodox_right_led_1_off();
      wait_ms(15);
      ergodox_right_led_3_on();
      ergodox_right_led_2_off();
      wait_ms(15);
      ergodox_right_led_2_on();
      ergodox_right_led_3_off();
      wait_ms(15);
      ergodox_right_led_1_on();
      wait_ms(15);
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_1_off();
      ergodox_right_led_2_off();
      wait_ms(15);
      
      wait_ms(15);
      ergodox_right_led_1_on();
      ergodox_right_led_3_off();
      ergodox_right_led_2_on();
      wait_ms(15);
      ergodox_right_led_1_off();
      wait_ms(15);
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_2_off();
      wait_ms(15);
      ergodox_right_led_3_off();
      wait_ms(15);
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_2_on();
      wait_ms(15);
      ergodox_right_led_1_off();
      ergodox_right_led_2_off();
      wait_ms(15);
      ergodox_right_led_1_on();
      ergodox_right_led_3_off();
      wait_ms(15);
      ergodox_right_led_3_on();
      ergodox_right_led_1_off();
      ergodox_right_led_2_on();
      wait_ms(15);
      ergodox_right_led_3_off();
      ergodox_right_led_1_on();
      wait_ms(15);
      
      wait_ms(15);
      ergodox_right_led_2_off();
      wait_ms(15);
      ergodox_right_led_1_off();
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_2_on();
      wait_ms(15);
      ergodox_right_led_3_off();
      ergodox_right_led_1_on();
      wait_ms(15);
      ergodox_right_led_1_off();
      
      wait_ms(15);
      ergodox_right_led_3_on();
      wait_ms(15);
      ergodox_right_led_3_off();
      ergodox_right_led_2_off();
      state->count = 0;
      reset_tap_dance(state);
  }
}

void meow_finished (qk_tap_dance_state_t *state, void *user_data) {
  meow_tap_state.state = cur_dance(state);
  if (state->count == 1) {
    int chance = rand() % 100;
    if (chance < 30) {
      SEND_STRING(SS_LCTL(SS_RALT(SS_LSFT(SS_TAP(X_M)))));
      ergodox_right_led_1_on();
      wait_ms(50);
      ergodox_right_led_2_on();
      wait_ms(50);
      ergodox_right_led_3_on();
      wait_ms(50);
      ergodox_right_led_1_off();
      wait_ms(50);
      ergodox_right_led_2_off();
      wait_ms(50);
      ergodox_right_led_3_off();
      wait_ms(25);
      ergodox_right_led_3_on();
      wait_ms(50);
      ergodox_right_led_2_on();
      wait_ms(50);
      ergodox_right_led_1_on();
      wait_ms(50);
      ergodox_right_led_3_off();
      wait_ms(50);
      ergodox_right_led_2_off();
      wait_ms(50);
      ergodox_right_led_1_off();
      reset_tap_dance(state);
    }
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [AT_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL,at_alt_finished, at_alt_reset,150),
  [F5_CLEAR_CACHE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL,f5_finished, f5_reset,200),
  [MEOW] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(meow,meow_finished,NULL,200)
};
