/*
 * initstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: Siegfried Mercelis
 */
#include "resultstate.h"

extern unsigned char black[];
extern unsigned char red[];
extern unsigned char red[];
extern unsigned char white[];
extern unsigned char blue[];
extern unsigned char yellow[];

extern force_data force;
extern frequency_data frequency;
void init_resultstate(MENU *state) {
	//initializes the ports
#ifdef STATETESTMODE
	printf("initializing state! \n");
#endif
	init_port();
	system("read");

}

void draw_resultstate(MENU *state){
	clr();
}

void handle_resultstate(MENU *state){
    TEXT output;
    output.row = 0;
    output.column=0;
    output.size=3;
	colorcopy(output.RGB, yellow);

	sprintf(output.text,"Result: %fN %fHz",force.force, frequency.frequency);
    draw_text(output);
    keysWaitOnPress();
	nextState = STATE_RECORD;
}

