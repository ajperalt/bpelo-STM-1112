/*
 * recordstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: Siegfried Mercelis
 */
#include "recordstate.h"

extern audio_settings audio_set;
extern float* data;
extern char *fileName;
extern char *noiseFile;
extern unsigned char black[];
extern unsigned char red[];
extern unsigned char red[];
extern unsigned char white[];
extern unsigned char blue[];
extern unsigned char yellow[];

void init_recordstate(MENU *state) {

#ifdef STATETESTMODE
	printf("initializing recordstate! \n");
#endif

	state->buttonCount = 2;
	state->buttons = malloc(sizeof(TEXTBUTTON) * state->buttonCount);

#ifdef STATETESTMODE
	printf("Buttons allocated.\n");
#endif

	colorcopy(state->bgcolor, yellow);
	//define button colors for this menu
	BUTTONCOLOR color;
	colorcopy(color.idleColor, blue);
	colorcopy(color.selectedColor, red);
	colorcopy(color.textColor, white);
	//draw textButtons
	setTextButton(&(state->buttons[0]), 40, 100, 1, 1, 3, UP, &color, "Record");
	setTextButton(&(state->buttons[1]), 150, 150, 1, 1, 3, UP, &color, "Cancel");
	state->activeButton = 0;

	updateButtonSelection(state);
}

void draw_recordstate(MENU *state) {
#ifdef STATETESTMODE
	printf("Clear state for record state->\n");
#endif
	set_bgcolor(state->bgcolor);
	clr();

	int i;
	for (i = 0; i < state->buttonCount; i++) {
		draw_text_button(state->buttons[i]);
	}
}

void handle_recordstate(MENU *state) {
#ifdef TESTMODE
	printf("Entered record state\n");
#endif
	TEXT output;
	output.row = 0;
	output.column = 0;
	output.size = 1;
	colorcopy(output.RGB, red);
	nextState = STATE_NULL;
	int stop = 0;
	while (stop == 0) {
		keysWaitOnPress();
		if ((keysGetLeft() == 1) || (keysGetRight() == 1)) {
			printf("buttonpress\n");
			state->activeButton += 1;
			if (state->activeButton == state->buttonCount) {
				state->activeButton = 0;
			}
			updateButtonSelection(state);
			refreshButtons(state);
		}
		if (keysGetEnter() == 1) {
			printf("ENTER\n");
			switch (state->activeButton) {
			case 0:
				//get global settings
				//--start of temporary data--//
				audio_set.duration = 0.250;
				audio_set.numChannels = 1;
				audio_set.sampleRate = 44100;
				audio_set.numSamples = audio_set.duration
						* audio_set.sampleRate;
				//--end of temporary data----//
				TEXT output;
				output.row = 0;
				output.column = 0;
				output.size = 2;
				colorcopy(output.RGB, red);
				//-----record audio-----
				sprintf(output.text, "RECORDING 250ms of NOISE\n");
				draw_text(output);
				output.row++;
				if (record_audio(noiseFile, &audio_set) < 0) {
					//error doorgeven
					nextState = STATE_NULL;
					break;
				}
				printf("record done");

				sprintf(output.text, "RECORDING\n");
				draw_text(output);
				output.row++;
				audio_set.duration = 0.450;
				if (record_audio(fileName, &audio_set) < 0) {

					//error doorgeven
					nextState = STATE_NULL;
					break;
				}
				printf("record done");
				nextState = STATE_CALCULATE;
				stop = 1;
				break;
			default:
				nextState = STATE_MAIN;
				stop = 1;
				break;
			}
		}
	}
}

