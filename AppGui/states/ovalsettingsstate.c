/*
 * ovalsettingsstate->c
 *
 *  Created on: Mar 31, 2011
 *      
 */

#ifdef DEBUG_STATES
#include <stdio.h>
#endif

#include <unistd.h>

#include "headers/introstate.h"
#include "headers/states.h"
#include "../settings/settings.h"

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/keys/sapim_keys.h"

#define LBL_TITLE	"lbl_title"
#define LBL_HEIGHT	"lbl_height"
#define LBL_WIDTH	"lbl_width"
#define	BTN_OK	"ok"
#define BTN_BACK "back"
#define	OVAL_WIDTH	80
#define	OVAL_HEIGHT	20
#define	SPN_WIDTH "spn_width"
#define SPN_HEIGHT "spn_height"

#define NAME_OVAL	"oval"


void init_ovalsettingsstate() {
	COMPONENT* lblTitle;
	COMPONENT* lblHeight;
	COMPONENT* lblWidth;
	COMPONENT* spnHeight;
	COMPONENT* spnWidth;
	COMPONENT* oval;
	COMPONENT* btnOk;
	COMPONENT* btnBack;

	int btnWidth, width;

#if DEBUG_STATES > 1
	printf("oval settings state! \n");
#endif
	containerClear();

	lblTitle = createLabel(LBL_TITLE, "set spoke measurements (in mm):", 10, 5);
	if (!lblTitle) {
		// error
	}

	lblHeight = createLabel(LBL_HEIGHT, "height:", 0, 0);
	if (!lblHeight) {
		// error
	}
	
	lblWidth = createLabel(LBL_WIDTH, "width:", 0, 0);
	if (!lblWidth) {
		// error
	}

	oval = createOval(NAME_OVAL, 0, componentGetBottom(lblTitle) + 5,
			OVAL_WIDTH, OVAL_HEIGHT, 0x00FF0000, GUI_PEN_SOLID);
	if (!oval) {
		// error
	}

	spnHeight = createSpinner(SPN_HEIGHT, 2, 0.01, 5, 0.01, 0, 0);
	if (!spnHeight) {
		// error
	}
	spinnerSetFocus(spnHeight, GUI_TRUE);
	
	spnWidth = createSpinner(SPN_WIDTH, 2, 0.01, 5, 0.01, 0, 0);
	if (!spnWidth) {
		// error
	}
	
	btnOk = createButton(BTN_OK, "OK", 20, 0);
	if (!btnOk) {
		// error
	}
	
	btnBack = createButton(BTN_BACK, "BACK", 20, 0);
	if (!btnBack) {
		// error
	}

	btnWidth = componentGetWidth(btnOk);
	width = componentGetWidth(oval);

	componentSetX(oval, 20);
	componentSetX(lblHeight, componentGetRight(oval) + 5);
	componentSetX(spnHeight, componentGetRight(lblHeight) + 5);
	componentSetY(lblHeight, componentGetBottom(oval) - componentGetHeight(
			oval) / 2 - componentGetHeight(lblHeight) / 2);
	componentSetY(spnHeight, componentGetBottom(oval) - componentGetHeight(
			oval) / 2 - componentGetHeight(spnHeight) / 2);
	
	componentSetX(lblWidth, componentGetX(oval));
	componentSetY(lblWidth, componentGetBottom(oval)+5);
	componentSetX(spnWidth, componentGetRight(lblWidth) +5);
	componentSetY(spnWidth, componentGetBottom(oval)+5);
	componentSetY(btnOk, componentGetBottom(spnWidth)+5);
	componentSetY(btnBack, componentGetBottom(btnOk)+5);
}

void draw_ovalsettingsstate() {
	containerInitIterator();

	while (containerHasNext()) {
		componentDraw(containerGetNext());
	}
}

int handle_ovalsettingsstate() {
	COMPONENT* buttons[4];
	MECHANIC_SETTINGS settings = getMechanicSettingsCopy();

	buttons[0] = containerGetComponent(SPN_HEIGHT);
	buttons[1] = containerGetComponent(SPN_WIDTH);
	buttons[2] = containerGetComponent(BTN_OK);
	buttons[3] = containerGetComponent(BTN_BACK);
	
	int current= 0;
	int stop = 0;
	int nextstate= -1;

	while (stop == 0) {
		keysWaitOnPress();
		if (keysGetDown() == 1) {
			current++;
			if (current == 4) {
				buttonSetFocus(buttons[3], GUI_FALSE);
				current = 0;
				spinnerSetFocus(buttons[current], GUI_TRUE);
			}else if (current==1) {
				spinnerSetFocus(buttons[current-1], GUI_FALSE);
				spinnerSetFocus(buttons[current], GUI_TRUE);
			}else if (current== 2) {
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
				current= 3;
				spinnerSetFocus(buttons[0], GUI_FALSE);
				buttonSetFocus(buttons[current], GUI_TRUE);
			break;
			case 0:
				spinnerSetFocus(buttons[current+1], GUI_FALSE);
				spinnerSetFocus(buttons[current], GUI_TRUE);
			break;
			case 1:
				buttonSetFocus(buttons[current+1], GUI_FALSE);
				spinnerSetFocus(buttons[current], GUI_TRUE);
			break;
			case 2:
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
			case 1:
				spinnerEnterSelectionMode(buttons[current]);
			break;
			case 2: // measure
				settings.type = MECHANIC_OVAL;
				settings.oval.diameterX = spinnerGetValue(buttons[1]);
				settings.oval.diameterY = spinnerGetValue(buttons[0]);
				setMechanicSettings(&settings);

				nextstate = STATE_RESULT;
				stop = 1;
			break;
			case 3:
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
