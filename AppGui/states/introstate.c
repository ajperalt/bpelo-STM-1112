/*
 * introstate->c
 *
 *  Created on: Mar 31, 2011
 *      Author: King Broos
 */

#ifdef DEBUG_STATES
#include <stdio.h>
#endif

#include "headers/introstate.h"
#include "headers/states.h"

#include "../../includes/gui/sapim_gui_all.h"
#include "../../includes/keys/sapim_keys.h"

#define	LBL_SAPIM			"lblSapim"
#define	LBL_RACING_SPOKES	"lblRacingSpokes"

void init_introstate() {
	COMPONENT* lblSapim;
	COMPONENT* lblRacingSpokes;

#ifdef DEBUG_STATES
	printf("Intro state! \n");
#endif
	containerClear();

	lblSapim = createLabel(LBL_SAPIM, "SAPIM", 100, 80);
	lblRacingSpokes = createLabel(LBL_RACING_SPOKES, "RACING SPOKES", 100, 100);

	if (!lblSapim || !lblRacingSpokes) {
		// error
	}

	componentSetFont(lblSapim, GUI_FONT_LARGEST);
}

void draw_introstate() {
	COMPONENT* lblSapim = containerGetComponent(LBL_SAPIM);
	COMPONENT* lblRacingSpokes = containerGetComponent(LBL_RACING_SPOKES);

	componentDraw(lblSapim);
	componentDraw(lblRacingSpokes);
}

int handle_introstate() {
#ifdef DEBUG_STATES
	printf("Handling intro\n");
#endif

	keysRefresh();
	keysWaitOnPress();

	return STATE_MAIN;
}
