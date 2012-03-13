/*
 * introstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */

#include "introstate.h"
extern unsigned char black[];
extern unsigned char white[];
extern unsigned char yellow[];


void init_introstate(MENU *state) {
	//initializes the ports
#ifdef STATETESTMODE
	printf("Intro state! \n");
#endif
	state->buttonCount = 2;
	state->buttons = malloc(sizeof(TEXTBUTTON) * state->buttonCount);
	BUTTONCOLOR color1, color2;
	colorcopy(color1.buttonColor, black);
	colorcopy(color1.textColor, white);
	colorcopy(color2.buttonColor, yellow);
	colorcopy(color2.textColor, black);

	setTextButton(&(state->buttons[0]), 100, 80, 1, 1, 3, DOWN, &color1,
			"SAPIM");
	setTextButton(&(state->buttons[1]), 100, 100, 1, 1, 3, UP, &color2,
			"RACING SPOKES");
	//textbutton racing spokes
	colorcopy(state->bgcolor, black);
}

void draw_introstate(MENU *state) {
	set_bgcolor(state->bgcolor);
	printf("bg set\n");
	clr();

	 int i;
	 for (i = 0; i < state->buttonCount; i++) {
	 draw_text_button(state->buttons[i]);
	 }

/*
	BITMAP * bmp = 0;
	load_bmp("images/sapimlogo.bmp", &bmp);
	bmp->p.x = 0;
	bmp->p.y = 0;
	draw_bitmap(bmp);
	*/

}

void handle_introstate(MENU *state) {
#ifdef TESTMODE
	printf("Handling intro\n");
#endif

	keysRefresh();
	keysWaitOnPress();

	printf("Key pressed\n");
	nextState = STATE_MAIN;
}
