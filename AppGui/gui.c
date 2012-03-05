/*
 * test.c
 *
 *  Created on: May 4, 2011
 *      Author: philip
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "states/headers/states.h"
#include "states/headers/initstate.h"
#include "states/headers/calculatingstate.h"
#include "states/headers/introstate.h"
#include "states/headers/mainstate.h"
#include "states/headers/measurestate.h"
#include "states/headers/roundsettingsstate.h"
#include "states/headers/roundedrectsettingsstate.h"
#include "states/headers/flatsettingsstate.h"
#include "states/headers/ovalsettingsstate.h"
#include "states/headers/settingsstate.h"
#include "states/headers/resultstate.h"


#include "../includes/serial/sapim_serial_all.h"
#include "../includes/gui/sapim_gui_all.h"

int main(void) {
	int state = STATE_INIT;

	while (state != -1) {
		switch (state) {
		case STATE_INIT:
			init_initstate();
			draw_initstate();
			state = handle_initstate();
			break;
		case STATE_INTRO:
			init_introstate();
			draw_introstate();
			state = handle_introstate();
			break;
		case STATE_MAIN:
			init_mainstate();
			draw_mainstate();
			state = handle_mainstate();
			break;
		case STATE_MEASURE:
			init_measurestate();
			draw_measurestate();
			state = handle_measurestate();
			break;
		case STATE_SETTINGS:
			init_settingsstate();
			draw_settingsstate();
			state = handle_settingsstate();
			break;

		case STATE_ROUNDSETTINGS:
			init_roundsettingsstate();
			draw_roundsettingsstate();
			state = handle_roundsettingsstate();
			break;
		case STATE_FLATSETTINGS:
			init_flatsettingsstate();
			draw_flatsettingsstate();
			state = handle_flatsettingsstate();
			break;
		case STATE_OVALSETTINGS:
			init_ovalsettingsstate();
			draw_ovalsettingsstate();
			state = handle_ovalsettingsstate();
			break;
		case STATE_ROUNDEDRECTSETTINGS:
			init_roundedrectsettingsstate();
			draw_roundedrectsettingsstate();
			state = handle_roundedrectsettingsstate();
			break;
		case STATE_RESULT:
			init_resultstate();
			draw_resultstate();
			state = handle_resultstate();
			break;
		default:
			state = -1;
		}
	}

	containerClear();

	return 0;
}
