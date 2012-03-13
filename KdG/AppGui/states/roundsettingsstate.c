/*
 * roundsettingsstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: pieter buytaert
 */

#ifdef DEBUG_STATES
#include <stdio.h>
#endif

#include <unistd.h>

#include "headers/introstate.h"
#include "headers/states.h"

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/keys/sapim_keys.h"
#include "../settings/settings.h"

#define LBL_TITLE	"lbl_title"
#define LBL_DIAMETER	"lbl_diameter"
#define	BTN_OK	"ok"
#define BTN_BACK "back"
#define SPN_DIAMETER "spn_diameter"

#define NAME_CIRCLE	"round"
#define CIRCLE_RADIUS	50

void init_roundsettingsstate() {
	COMPONENT* lblTitle;
	COMPONENT* lblDiameter;
	COMPONENT* spnDiameter;
	COMPONENT* circle;
	COMPONENT* btnOk;
	COMPONENT* btnBack;

	int btnWidth, circleWidth;

#if DEBUG_STATES > 1
	printf("round settings state! \n");
#endif
	containerClear();

	lblTitle = createLabel(LBL_TITLE, "set spoke measurements (in mm):", 10, 5);
	if (!lblTitle) {
		// error
	}

	lblDiameter = createLabel(LBL_DIAMETER, "Diameter:", 0, 0);
	if (!lblDiameter) {
		// error
	}

	circle = createCircle(NAME_CIRCLE, 0, componentGetBottom(lblTitle) + 5,
			CIRCLE_RADIUS, 0x00FF0000, GUI_PEN_SOLID);
	if (!circle) {
		// error
	}

	spnDiameter = createSpinner(SPN_DIAMETER, 2, 0.01, 5, 0.01, 0, 0);
	if (!spnDiameter) {
		// error
	}
	spinnerSetFocus(spnDiameter, GUI_TRUE);
	
	btnOk = createButton(BTN_OK, "OK", 20, componentGetBottom(
			circle) + 10);
	if (!btnOk) {
		// error
	}
	
	btnBack = createButton(BTN_BACK, "BACK", 20, componentGetBottom(
			btnOk) + 10);
	if (!btnBack) {
		// error
	}

	btnWidth = componentGetWidth(btnOk);
	circleWidth = componentGetWidth(circle);

	componentSetX(circle, (btnWidth - circleWidth) / 2 + componentGetX(btnOk));
	componentSetX(lblDiameter, componentGetRight(circle) + 5);
	componentSetX(spnDiameter, componentGetRight(lblDiameter) + 5);
	componentSetY(lblDiameter, componentGetBottom(circle) - componentGetHeight(
			circle) / 2 - componentGetHeight(lblDiameter) / 2);
	componentSetY(spnDiameter, componentGetBottom(circle) - componentGetHeight(
			circle) / 2 - componentGetHeight(spnDiameter) / 2);

}

void draw_roundsettingsstate() {
	containerInitIterator();

	while (containerHasNext()) {
		componentDraw(containerGetNext());
	}
}

int handle_roundsettingsstate() {
	MECHANIC_SETTINGS settings = getMechanicSettingsCopy();
	COMPONENT* buttons[3];
	buttons[0] = containerGetComponent(SPN_DIAMETER);
	buttons[1] = containerGetComponent(BTN_OK);
	buttons[2] = containerGetComponent(BTN_BACK);
	
	int current= 0;
	int stop = 0;
	int nextstate= -1;

	settings.type = MECHANIC_ROUND;

	while (stop == 0) {
		keysWaitOnPress();
		if (keysGetDown() == 1) {
			current++;
			if (current == 3) {
				buttonSetFocus(buttons[2], GUI_FALSE);
				current = 0;
				spinnerSetFocus(buttons[current], GUI_TRUE);
			}else if (current== 1) {
				spinnerSetFocus(buttons[current-1], GUI_FALSE);
				buttonSetFocus(buttons[current], GUI_TRUE);
			}else {
				buttonSetFocus(buttons[current-1], GUI_FALSE);
				buttonSetFocus(buttons[current], GUI_TRUE);
			}
		} else if (keysGetUp() == 1) {
			current--;
			switch (current) {
			case -1: // measure
				current= 2;
				spinnerSetFocus(buttons[0], GUI_FALSE);
				buttonSetFocus(buttons[current], GUI_TRUE);
			break;
			case 0:
				buttonSetFocus(buttons[current+1], GUI_FALSE);
				spinnerSetFocus(buttons[current], GUI_TRUE);
			break;
			case 1:
				buttonSetFocus(buttons[current+1], GUI_FALSE);
				buttonSetFocus(buttons[current], GUI_TRUE);
			break;
			default:
				nextstate = -1;
				stop = 1;
			}
		} else if (keysGetEnter() == 1) {
			switch (current) {
			case 0:
				spinnerEnterSelectionMode(buttons[current]);
			break;
			case 1: // measure
				settings.round.diameter = spinnerGetValue(buttons[0]);
				setMechanicSettings(&settings);

				nextstate = STATE_RESULT;
				stop = 1;
			break;
			case 2:
				nextstate = STATE_MEASURE;
				stop=1;
			break;
			default:
				nextstate = -1;
				stop = 1;
			}
		}
	}

	containerClear();

	return nextstate;
}
