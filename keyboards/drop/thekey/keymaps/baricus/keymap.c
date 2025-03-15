/* Copyright 2021 Joe Maples <joe@maples.dev>
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

enum layers { FN_KEYS = 0, COPY_PASTE };

enum tap_dancing { TAP_17_20 = 0, TAP_21_24 };

// tap the function keys as needed

void handle_taps(int base, int count) {
    // ensures we have the right max and min values
    // NOTE: this is TAPS, not offset, so we subtract 1
    count = count < 1 ? 1 : count;
    count = count > 4 ? 4 : count;
    count -= 1;

    if (base == 17) {
        tap_code(KC_F17 + count);
    } else if (base == 21) {
        tap_code(KC_F21 + count);
    } else {
        SEND_STRING("YOU FUCKED UP, BUCKO");
    }
}

// man I wish I had lambdas :(
void tap_17(tap_dance_state_t *state, void *user_data) {
    if (state != NULL) {
        handle_taps(17, state->count);
    }
}

void tap_21(tap_dance_state_t *state, void *user_data) {
    if (state != NULL) {
        handle_taps(21, state->count);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TAP_17_20] = ACTION_TAP_DANCE_FN(tap_17),
    [TAP_21_24] = ACTION_TAP_DANCE_FN(tap_21),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [FN_KEYS] = LAYOUT(
        /*MO(COPY_PASTE) , TD(TAP_17_20) , TD(TAP_21_24)*/
        S(KC_GRV), KC_C, KC_V
    ),
    [COPY_PASTE] = LAYOUT(_______, LCTL(KC_C), LCTL(KC_V)),

};
