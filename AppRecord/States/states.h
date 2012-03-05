/*
 * states.h
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */

#ifndef STATES_H_
#define STATES_H_
#include "../LCD/Drawing/draw.h"
#include "../LCD/Misc/vars.h"
#include "nullstate.h"
#include "initstate.h"
#include "introstate.h"
#include "calculatingstate.h"
#include "recordstate.h"
#include "resultstate.h"
#include "mainstate.h"

typedef struct {
	TEXT title;
	unsigned char bgcolor[3];
	int activeButton;
	int buttonCount;
	TEXTBUTTON *buttons;
	TEXT *text;

} MENU;


void updateButtonSelection(MENU *state);
void refreshButtons(MENU *state);

#endif /* STATES_H_ */
