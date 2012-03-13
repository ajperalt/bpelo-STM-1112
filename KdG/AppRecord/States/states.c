/*
 * states.c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */
#include "states.h"

void updateButtonSelection(MENU *state) {
	int i;
	for (i = 0; i <= state->buttonCount; i++) {
		if (i == state->activeButton) {
			colorcopy(state->buttons[i].color.buttonColor,
					state->buttons[i].color.selectedColor);
		} else {
			colorcopy(state->buttons[i].color.buttonColor,
					state->buttons[i].color.idleColor);
		}
	}
}

void refreshButtons(MENU *state) {
	int i;
	for (i = 0; i <= state->buttonCount; i++) {
		draw_text_button(state->buttons[i]);
	}
}
