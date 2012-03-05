/*
 * initstate.c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */
#include "calculatingstate.h"

extern audio_settings audio_set;
extern float *data;
extern frequency_data frequency;
extern force_data force;
extern spoke_data spoke;
extern char *fileName;
extern unsigned char red[];

void init_calculatingstate(MENU *state) {
	//initializes the ports
#ifdef STATETESTMODE
		printf("initializing state! \n");
#endif
}

void draw_calculatingstate(MENU *state){
	clr();
	TEXT output;
	sprintf(output.text,"CALCULATING FFT\n");
    output.row = 0;
    output.column=0;
    output.size=2;
    colorcopy(output.RGB, red);
	draw_text(output);
}

void handle_calculatingstate(MENU *state){
	//GUI OUTPUT -->
    TEXT output;
    output.row = 1;
    output.column=0;
    output.size=2;
    colorcopy(output.RGB, red);
	sprintf(output.text, "READING\n");
	draw_text(output);
	output.row++;
	//<--GUI OUTPUT

	audio_set.numSamples = read_audio(fileName, &data);
	if (audio_set.numSamples <= 0) {
		//error doorgeven
		nextState = STATE_NULL;
		return;
	}
    if (getFrequency(data,audio_set.numSamples, &frequency) < 0) {
    	sprintf(output.text,"Error calculating frequency...");
    } else {
    	sprintf(output.text,"The recorded frequency is: %.2f with precision %.2f\n",frequency.frequency, frequency.precision);
    }
    free(data);
    data = 0;
    draw_text(output);

    output.row++;
    output.row++;
    sprintf(output.text,"CALCULATING FORCE\n");
    draw_text(output);
    output.row++;
    output.row++;
    if (getForce(&spoke,&frequency,&force) >= 0) {
        sprintf(output.text,"The calculated force is: %.2f with offset %.2f and was found after %d iterations.",force.force,force.offset,force.iterations);
        nextState = STATE_MAIN;
    } else {
        sprintf(output.text,"Error calculating force");
        draw_text(output);
        nextState = STATE_NULL;
    }
    draw_text(output);
    output.row++;
    output.row++;
    sprintf(output.text,"Press any key to return to menu");
    draw_text(output);
    keysWaitOnPress();
}

