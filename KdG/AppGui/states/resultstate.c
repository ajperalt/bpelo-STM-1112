/*
 * resultstate.c
 *
 *  Created on: May 20, 2011
 *      Author: philip
 */

#include <stdlib.h>
#include <stdio.h>

#include "headers/introstate.h"
#include "headers/states.h"

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/gui/settings/sapim_gui_settings.h"
#include "../../includes/keys/sapim_keys.h"
#include "../../includes/enable/sapim_enable.h"
#include "../../includes/mechanics/sapim_mech_structs.h"
#include "../settings/settings.h"

#define	LBL_TITLE			"lblTitle"
#define LBL_RECORD_NOISE	"lblRecord"
#define LBL_PULS			"lblPuls"
#define	LBL_ANALYSE			"lblAnalyze"
#define	LBL_MECHANICS		"lblMechanics"
#define	LBL_RESULT			"lblResult"

void init_resultstate() {
	COMPONENT *component;

	containerClear();

	component = createLabel(LBL_TITLE, "Result", 5, 5);
	if (!component) {
		// error;
	}

	component = createLabel(LBL_RECORD_NOISE, "Recording Noise", 5,
			componentGetBottom(component) + 15);
	if (!component) {
		// error;
	}

	component = createLabel(LBL_PULS, "Generating pulse and recording signal",
			5, componentGetBottom(component) + 5);
	if (!component) {
		// error;
	}

	component = createLabel(LBL_ANALYSE, "Analyzing...", 5, componentGetBottom(
			component) + 5);
	if (!component) {
		// error;
	}

	component = createLabel(LBL_MECHANICS, "Calculating force", 5,
			componentGetBottom(component) + 5);
	if (!component) {
		// error;
	}

	component = createLabel(LBL_RESULT, "", 5, componentGetBottom(component)
			+ 5);
	if (!component) {
		// error;
	}

	componentSetFont(component, GUI_FONT_LARGEST);
	componentSetForegroundColor(component, 0x00FF0000);

	disable(GPIO_SOLENOID);
}

void draw_resultstate() {
	componentDraw(containerGetComponent(LBL_TITLE));
}

int handle_resultstate() {
	FILE *output, *input;
	force_data result;
	char buff[255];

	output = input = 0;

	if (getAudioSettingsReference()->noisefilterEnabled == SETTINGS_FALSE) {
		componentSetText(containerGetComponent(LBL_RECORD_NOISE),
				"Noise filter disabled");
		componentDraw(containerGetComponent(LBL_RECORD_NOISE));
	} else {
		componentDraw(containerGetComponent(LBL_RECORD_NOISE));
		system("./Recorder workspace/noisedata.raw");
	}

	componentDraw(containerGetComponent(LBL_PULS));
	enable(GPIO_SOLENOID);
	system("./Recorder workspace/audiodata.raw");
	disable(GPIO_SOLENOID);

	componentDraw(containerGetComponent(LBL_ANALYSE));
	system("./Analyzer");

	output = fopen("workspace/mechanics_inputs.dat", "wb");
	if (!output) {
		componentSetText(containerGetComponent(LBL_RESULT),
				"Couldn't write the mechanics information!");
	} else {
		fwrite(getMechanicSettingsReference(), sizeof(MECHANIC_SETTINGS), 1,
				output);
		fclose(output);

		system("./Mechanics");

		input = fopen("workspace/result.dat", "rb");
		if (!input) {
			componentSetText(containerGetComponent(LBL_RESULT),
					"Couldn't read the result!");
		} else {
			fread(&result, sizeof(force_data), 1, input);
			fclose(input);
			if(result.force > 350 && result.force < 2050) {
				sprintf(buff, "Force: %fN", result.force);
			} else {
				sprintf(buff, "Force out of range!");
			}

			componentSetText(containerGetComponent(LBL_RESULT), buff);
		}
	}

	componentDraw(containerGetComponent(LBL_RESULT));

	system("rm ./workspace/*");

	keysWaitOnPress();
	containerClear();
	return STATE_MAIN;
}
