/*
 * initstate.c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */

#ifdef DEBUG_STATES
#include <stdio.h>
#endif

#include "headers/initstate.h"
#include "headers/states.h"
#include "../settings/settings.h"

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/serial/sapim_serial_all.h"
#include "../../includes/enable/sapim_enable.h"
#include "../../includes/keys/sapim_keys.h"

void init_initstate() {
	//initializes the ports
#ifdef DEBUG_STATES
	printf("initializing state! \n");
#endif
	/*
	 * init outputs
	 */
	enableInit(GPIO_LCD_RESET, IO_DIRECTION_OUT, IO_ACTIVE_LOW, 0);
	enableInit(GPIO_MIC, IO_DIRECTION_OUT, IO_ACTIVE_LOW, 0);
	enableInit(GPIO_SOLENOID, IO_DIRECTION_OUT, IO_ACTIVE_LOW, 0);

	keysInit();
	serialInitPort();
	guiInit();

	initSettings();
}

void draw_initstate() {
#ifdef DEBUG_STATES
	printf("initializing screen...\n");
	//getchar();
#endif
	clearScreen();
}

int handle_initstate() {
#ifdef DEBUG_STATES
	printf("handling initstate");
#endif
	// hier mss libs voor keys laden
	return STATE_INTRO;
}

