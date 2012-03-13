/*
 * initstate.h
 *
 *  Created on: Mar 31, 2011
 *      Author: Siegfried Mercelis
 */

#ifndef RECORDSTATE_H_
#define RECORDSTATE_H_
#include "../LCD/Drawing/draw.h"
#include "../LCD/Misc/vars.h"
#include "../AUDIO/include/audio.h"
#include "../AUDIO/include/record.h"
#include "../includes/sapim_structs.h"
#include "../includes/sapim_all.h"
#include "states.h"

void init_recordstate();
void draw_recordstate();
void handle_recordstate();
/*
 typedef struct {
 TEXT title;
 TEXTBUTTON Startrecord;
 //these colors define when a button is idle or selected (not pressed) the pressed color
 //equals the selectedcolor
 unsigned char idlecolor[3];
 unsigned char selectedcolor[3];
 unsigned char bgcolor[3];
 TEXTBUTTON buttons[5];
 int activeButton;
 } RECORDSTATE;*/

#endif /* RECORDSTATE_H_ */
