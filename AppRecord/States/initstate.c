/*
 * initstate.c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */
#include "initstate.h"

void init_initstate(MENU *state) {
	//initializes the ports
#ifdef STATETESTMODE
	printf("initializing state! \n");
#endif
	init_port();
	//getchar();

}

void draw_initstate(MENU *state) {
#ifdef TESTMODE
	printf("initializing screen...\n");
	//getchar();
#endif
	init_screen();
}

void handle_initstate(MENU *state) {
#ifdef TESTMODE
	printf("handling initstate");
#endif
	// hier mss libs voor keys laden
	nextState = STATE_INTRO;
}

