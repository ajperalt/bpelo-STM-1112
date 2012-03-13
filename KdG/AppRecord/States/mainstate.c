/*
 * mainstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: kdg1
 */

#ifndef MAINSTATE_C_
#define MAINSTATE_C_

#include "mainstate.h"

extern unsigned char black[];
extern unsigned char red[];
extern unsigned char blue[];
extern unsigned char white[];

void init_mainstate(MENU *state) {
#ifdef STATETESTMODE
	printf("Main menu state! \n");
#endif
	state->activeButton = 0;
	state->buttonCount = 5;
	state->buttons = malloc(sizeof(TEXTBUTTON) * state->buttonCount);
	colorcopy(state->bgcolor, red);
#ifdef STATETESTMODE
	printf("Buttons allocated.\n");
#endif

	//text intro
	state->title.column = 1;
	state->title.row = 1;
	state->title.size = 3;
	colorcopy(state->title.RGB, black);
	strcpy(state->title.text, "Choose your option:");

	//draw textButtons
	BUTTONCOLOR color;
	colorcopy(color.idleColor, blue);
	colorcopy(color.selectedColor, red);
	colorcopy(color.textColor, white);

	setTextButton(&(state->buttons[0]), 40, 40, 1, 1, 3, UP, &color, "Measure");
	setTextButton(&(state->buttons[1]), 40, 70, 1, 1, 3, UP, &color, "Settings");
	setTextButton(&(state->buttons[2]), 40, 100, 1, 1, 3, UP, &color,
			"Calibrate");
	setTextButton(&(state->buttons[3]), 40, 130, 1, 1, 3, UP, &color, "Sleep");
	setTextButton(&(state->buttons[4]), 40, 160, 1, 1, 3, UP, &color,
			"Shut down");
	updateButtonSelection(state);
}

void draw_mainstate(MENU *state) {
	printf("Drawing mainstate->\n");
	int i;
	/*set_bgcolor(mainstate->bgcolor);
	 printf("bgset\n");*/
	clr();
	printf("scrclear\n");
	draw_text(state->title);
	for (i = 0; i < state->buttonCount; i++) {
		draw_text_button(state->buttons[i]);
	}

}

void handle_mainstate(MENU *state) {
#ifdef STATETESTMODE
	printf("Handling main state");
#endif

	int stop = 0;
	while (stop == 0) {
		keysWaitOnPress();
		if (keysGetDown() == 1) {
			printf("buttonpress\n");
			state->activeButton += 1;
			if (state->activeButton == state->buttonCount) {
				state->activeButton = 0;
			}
			updateButtonSelection(state);
			refreshButtons(state);
		} else if (keysGetUp() == 1) {
			printf("buttonpress\n");
			state->activeButton -= 1;
			if (state->activeButton == -1) {
				state->activeButton = state->buttonCount - 1;
			}
			updateButtonSelection(state);
			refreshButtons(state);
		}
		if (keysGetEnter() == 1) {
			printf("ENTER\n");
			switch (state->activeButton) {
			case 0:
				printf("goto record\n");
				nextState = STATE_RECORD;
				stop = 1;
				break;
			default:
				printf("ERROR\n");
				nextState = STATE_NULL;
				stop = 1;
				break;
			}
		}
	}
}

#endif /* MAINSTATE_C_ */

