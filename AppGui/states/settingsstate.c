/*
 * settingsstate.c
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/keys/sapim_keys.h"
#include "../../includes/gui/settings/sapim_gui_settings.h"

#include "headers/settingsstate.h"
#include "headers/states.h"

#include "../settings/settings.h"

#define	LBL_TITLE		"lblSettings"
#define	LBL_NOISEFILTER	"lblNoiseFilter"
#define BTN_ONOFF		"btnOnOff"
#define BTN_OK			"btnOk"
#define BTN_CANCEL		"btnCancel"

void init_settingsstate() {
	int x, y, width;
	COMPONENT *lblTitle;
	COMPONENT *lblNoiseFilter;
	COMPONENT *btnOnOff;
	COMPONENT *btnOk;
	COMPONENT *btnCancel;

	containerClear();

	lblTitle = createLabel(LBL_TITLE, "Settings", 5, 5);
	lblNoiseFilter = createLabel(LBL_NOISEFILTER, "Noisefilter: ", 25,
			componentGetBottom(lblTitle) + 10);

	btnOnOff
			= createButton(BTN_ONOFF,
					(getAudioSettingsReference()->noisefilterEnabled
							== SETTINGS_TRUE ? "On" : "Off"), 0, 0);

	btnOk = createButton(BTN_OK, "Ok", 0, 0);
	btnCancel = createButton(BTN_CANCEL, "Cancel", 0, 0);

	x = componentGetRight(lblNoiseFilter);
	y = (componentGetHeight(lblNoiseFilter) - componentGetHeight(btnOnOff)) / 2
			+ componentGetY(lblNoiseFilter);
	componentSetLocation(btnOnOff, x, y);

	componentSetY(btnOk, getDisplayHeight() - componentGetHeight(btnOk) - 5);
	componentSetY(btnCancel, componentGetY(btnOk));

	width = componentGetWidth(btnOk) + componentGetWidth(btnCancel) + 5;
	componentSetX(btnOk, (getDisplayWidth() - width) / 2);
	componentSetX(btnCancel, componentGetRight(btnOk) + 5);

	if (getAudioSettingsReference()->noisefilterEnabled == SETTINGS_TRUE) {
		buttonSetBackgroundColor(btnOnOff, 0x0000FF00);
		buttonSetBackgroundFocusColor(btnOnOff, 0x0000BB00);
	} else {
		buttonSetBackgroundColor(btnOnOff, 0x00FF0000);
		buttonSetBackgroundFocusColor(btnOnOff, 0x00BB0000);
	}
}

void draw_settingsstate() {
	containerInitIterator();

	while (containerHasNext()) {
		componentDraw(containerGetNext());
	}
}

int handle_settingsstate() {
	COMPONENT *buttons[3];
	int done = -1;
	int current = 0;
	AUDIO_SETTINGS settings = getAudioSettingsCopy();

	buttons[0] = containerGetComponent(BTN_ONOFF);
	buttons[1] = containerGetComponent(BTN_OK);
	buttons[2] = containerGetComponent(BTN_CANCEL);

	buttonSetFocus(buttons[current], GUI_TRUE);

	keysWaitOnPress();
	while (done == -1) {
		if (keysGetUp() == KEYS_TRUE) {
			buttonSetFocus(buttons[current++], GUI_FALSE);

			if (current == 3) {
				current = 0;
			}

			buttonSetFocus(buttons[current], GUI_TRUE);
		} else if (keysGetDown() == KEYS_TRUE) {
			buttonSetFocus(buttons[current--], GUI_FALSE);

			if (current == -1) {
				current = 2;
			}

			buttonSetFocus(buttons[current], GUI_TRUE);
		} else if (keysGetEnter() == KEYS_TRUE) {
			switch (current) {
			case 0:
				buttonSetState(buttons[0], GUI_BTN_DOWN);
				while (keysGetEnter() == KEYS_TRUE) {
					keysRefresh();
				}

				if (settings.noisefilterEnabled == SETTINGS_TRUE) {
					settings.noisefilterEnabled = SETTINGS_FALSE;
					componentSetText(buttons[0], "Off");
					buttonSetBackgroundColor(buttons[0], 0x00FF0000);
					buttonSetBackgroundFocusColor(buttons[0], 0x00BB0000);
				} else {
					settings.noisefilterEnabled = SETTINGS_TRUE;
					componentSetText(buttons[0], "On");
					buttonSetBackgroundColor(buttons[0], 0x0000FF00);
					buttonSetBackgroundFocusColor(buttons[0], 0x0000FF00);
				}
				buttonSetState(buttons[0], GUI_BTN_UP);
				break;
			case 1:
				setAudioSettings(&settings);
				done = 1;
				break;
			case 2:
				done = 1;
			}
		}

		if (done == -1) {
			keysWaitOnPress();
		}
	}

	return STATE_MAIN;
}
