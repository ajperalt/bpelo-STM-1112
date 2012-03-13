/*
 * nullstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */
#include "nullstate.h"
extern unsigned char black[];
extern unsigned char red[];
extern unsigned char red[];
extern unsigned char white[];
extern unsigned char blue[];

void init_nullstate(MENU *state) {
#ifdef STATETESTMODE
	printf("null state! \n");
#endif
	state->buttonCount = 2;
	state->activeButton = 0;
	state->buttons = malloc(sizeof(TEXTBUTTON) * state->buttonCount);

#ifdef STATETESTMODE
	printf("Buttons allocated.\n");
#endif

	colorcopy(state->bgcolor, red);
	//define button colors for this menu
	BUTTONCOLOR color;
	colorcopy(color.idleColor, white);
	colorcopy(color.textColor, black);
	//draw textButtons
	setTextButton(&(state->buttons[0]), 100, 100, 1, 1, 4, UP, &color,
			"STATE ERROR");
	setTextButton(&(state->buttons[1]), 40, 140, 1, 1, 3, UP, &color,
			"Press any key to restart.");
}

void draw_nullstate(MENU *state) {
	set_bgcolor(state->bgcolor);
	clr();

	int i;
	for (i = 0; i < state->buttonCount; i++) {
		draw_text_button(state->buttons[i]);
	}

}

void handle_nullstate(MENU *state) {
	//event handling based on GPIO buttons
	/*
	 * in de trand van: if(ok = pressed) : state->button.state = DOWN
	 * nextState
	 */
#ifdef TESTMODE
	printf("Fatal Error.\n");
#endif

	keysClear();
	keysRefresh();
	keysWaitOnPress();
	nextState = STATE_MAIN;
}

