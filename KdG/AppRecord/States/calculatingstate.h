/*
 * initstate.h
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */

#ifndef CALCULATINGSTATE_H_
#define CALCULATINGSTATE_H_
#include "../LCD/Drawing/draw.h"
#include "../LCD/Misc/vars.h"
#include "../MECH/include/mechanics.h"
#include "../includes/sapim_structs.h"
#include "../includes/sapim_all.h"
#include "../AUDIO/include/fft.h"
#include "../AUDIO/include/audio.h"
#include "../States/states.h"
void init_calculatingstate();
void draw_calculatingstate();
void handle_calculatingstate();

#endif /* CALCULATINGSTATE_H_ */
