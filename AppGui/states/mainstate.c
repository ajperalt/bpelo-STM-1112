/*
 * mainstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: kdg1
 */

#ifndef MAINSTATE_C_
#define MAINSTATE_C_

#ifdef DEBUG_STATES
#include <stdio.h>
#endif

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/keys/sapim_keys.h"

#include "headers/mainstate.h"
#include "headers/states.h"

#define	BTN_MEASURE		"cmd_measure"
#define	BTN_SETTINGS	"cmd_settings"
#define BTN_CALIBRATE	"cmd_calibrate"
#define	BTN_SLEEP		"cmd_sleep"
#define BTN_SHUTDOWN	"cmd_shutdown"

#define	LBL_TITLE		"lbl_title"

void init_mainstate() {
	COMPONENT *btnMeasure, *btnSettings, *btnCalibrate, *btnSleep, *btnShutdown;
	COMPONENT *lblTitle;

#ifdef DEBUG_STATES
	printf("Main menu state! \n");
#endif

#if DEBUG_STATES > 1
	printf("Debug: clearing container\n");
#endif
	containerClear();

#if DEBUG_STATES > 1
	printf("Debug: container cleared\n");
#endif

	lblTitle = createLabel(LBL_TITLE, "Choose your option: ", 10, 5);
	btnMeasure = createButton(BTN_MEASURE, "Measure", 40, 40);
	btnSettings = createButton(BTN_SETTINGS, "Settings", 40,
			componentGetBottom(btnMeasure) + 5);
	btnCalibrate = createButton(BTN_CALIBRATE, "Calibrate", 40,
			componentGetBottom(btnSettings) + 5);
	btnSleep = createButton(BTN_SLEEP, "Sleep", 40, componentGetBottom(
			btnCalibrate) + 5);
	btnShutdown = createButton(BTN_SHUTDOWN, "Shut down", 40,
			componentGetBottom(btnSleep) + 5);

	if (!lblTitle || !btnMeasure || !btnSettings || !btnCalibrate || !btnSleep
			|| !btnShutdown) {
		// error
	}

#if DEBUG_STATES > 1
	printf("Debug: labels and buttons created\n");
#endif
}

void draw_mainstate() {
#if DEBUG_STATES > 1
	printf("Debug: Drawing main screen\n");
#endif
	containerInitIterator();
	while (containerHasNext()) {
		componentDraw(containerGetNext());
	}

#if DEBUG_STATES > 1
	printf("Debug: Main screen drawed\n");
#endif
}

int handle_mainstate() {
#ifdef DEBUG_STATES
	printf("Handling main state");
#endif

	int stop = 0;
	int current = 0;
	int nextstate = -1;
	COMPONENT* buttons[5];
	buttons[0] = containerGetComponent(BTN_MEASURE);
	buttons[1] = containerGetComponent(BTN_SETTINGS);
	buttons[2] = containerGetComponent(BTN_CALIBRATE);
	buttons[3] = containerGetComponent(BTN_SLEEP);
	buttons[4] = containerGetComponent(BTN_SHUTDOWN);

	buttonSetFocus(buttons[current], GUI_TRUE);

	while (nextstate == -1) {
		keysWaitOnPress();
		if (keysGetDown() == 1) {
			buttonSetFocus(buttons[current++], GUI_FALSE);
			if (current == 5) {
				current = 0;
			}

			buttonSetFocus(buttons[current], GUI_TRUE);
		} else if (keysGetUp() == 1) {
			buttonSetFocus(buttons[current--], GUI_FALSE);
			if (current == -1) {
				current = 4;
			}

			buttonSetFocus(buttons[current], GUI_TRUE);
		} else if (keysGetEnter() == 1) {
			switch (current) {
			case 0:	// measure
				nextstate = STATE_MEASURE;
				stop = 1;
				break;
			case 1: // settings
				nextstate = STATE_SETTINGS;
				break;
			default:
				nextstate = -1;
			}
		}
	}

	return nextstate;
}

#endif /* MAINSTATE_C_ */

