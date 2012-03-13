/*
 * measurestate->c
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

#define LBL_TITLE	"lbl_title"
#define	BTN_ROUND	"rnd_spokes"
#define BTN_FLAT	"flt_spokes"
#define BTN_OVAL	"oval_spokes"
#define BTN_ROUNDRECT	"rndrct_spokes"

#define NAME_CIRCLE	"round"
#define CIRCLE_RADIUS	10

#define	NAME_RECT	"flatten"
#define	RECT_WIDTH	80
#define	RECT_HEIGHT	10

#define NAME_OVAL	"oval"
#define OVAL_X		33
#define	OVAL_Y		10

#define NAME_ROUND_RECT	"roundrect"
#define RND_RECT_OUTER_WIDTH	80
#define RND_RECT_INNER_WIDTH	60
#define RND_RECT_HEIGHT			15

void init_measurestate() {
	COMPONENT* lblTitle;
	COMPONENT* btnRound;
	COMPONENT* circle;
	COMPONENT* btnFlat;
	COMPONENT* rectangle;
	COMPONENT* btnOval;
	COMPONENT* oval;
	COMPONENT* btnRoundRect;
	COMPONENT* roundrect;

	int btnWidth, circleWidth, rectWidth, ovalWidth, roundrectWidth;

#if DEBUG_STATES > 1
	printf("Measure state! \n");
#endif
	containerClear();

	lblTitle = createLabel(LBL_TITLE, "Select spoke type:", 10, 5);
	if (!lblTitle) {
		// error
	}

	circle = createCircle(NAME_CIRCLE, 0, componentGetBottom(lblTitle) + 5,
			CIRCLE_RADIUS, 0x00FF0000, GUI_PEN_SOLID);
	if (!circle) {
		// error
	}

	btnRound = createButton(BTN_ROUND, "Round spoke", 20, componentGetBottom(
			circle) + 2);
	if (!btnRound) {
		// error
	}

	rectangle = createRectangle(NAME_RECT, 0, componentGetBottom(btnRound) + 5,
			RECT_WIDTH, RECT_HEIGHT, 0x00FF0000, GUI_PEN_SOLID);
	if (!rectangle) {
		// error
	}

	btnFlat = createButton(BTN_FLAT, "Flatten spoke", 20, componentGetBottom(
			rectangle) + 2);
	if (!btnFlat) {
		// error
	}

	oval = createOval(NAME_RECT, 0, componentGetBottom(btnFlat) + 5, OVAL_X,
			OVAL_Y, 0x00FF0000, GUI_PEN_SOLID);
	if (!oval) {
		// error
	}

	btnOval = createButton(BTN_OVAL, "Oval spoke", 20, componentGetBottom(oval)
			+ 2);
	if (!btnOval) {
		// error
	}

	roundrect = createRoundrect(NAME_ROUND_RECT, 0, componentGetBottom(btnOval)
			+ 5, RND_RECT_OUTER_WIDTH, RND_RECT_INNER_WIDTH, RND_RECT_HEIGHT,
			0x00FF0000, GUI_PEN_SOLID);
	if (!roundrect) {
		// error
	}

	btnRoundRect = createButton(BTN_ROUNDRECT, "Rounded rect spoke", 20,
			componentGetBottom(roundrect) + 2);
	if (!btnRoundRect) {
		// error
	}

	btnWidth = componentGetWidth(btnRound);
	circleWidth = componentGetWidth(circle);
	rectWidth = componentGetWidth(rectangle);
	ovalWidth = componentGetWidth(oval);
	roundrectWidth = componentGetWidth(roundrect);

	componentSetX(circle, (btnWidth - circleWidth) / 2
			+ componentGetX(btnRound));

	btnWidth = componentGetWidth(btnFlat);
	componentSetX(rectangle, (btnWidth - rectWidth) / 2
			+ componentGetX(btnFlat));

	btnWidth = componentGetWidth(btnOval);
	componentSetX(oval, (btnWidth - ovalWidth) / 2 + componentGetX(btnOval));

	btnWidth = componentGetWidth(btnRoundRect);
	componentSetX(roundrect, (btnWidth - roundrectWidth) / 2 + componentGetX(
			btnRoundRect));

#if DEBUG_STATES > 1
	printf("Rectangle:\nx: %d\ny: %d\nwidth: %d\nheight: %d\n", componentGetX(
					rectangle), componentGetY(rectangle), componentGetWidth(rectangle),
			componentGetHeight(rectangle));
	fflush(stdout);
#endif
}

void draw_measurestate() {
	containerInitIterator();

	while (containerHasNext()) {
		componentDraw(containerGetNext());
	}
}

int handle_measurestate() {
#ifdef DEBUG_STATES
	printf("Handling intro\n");
#endif

	int stop = 0;
	int current = 0;
	int nextstate = -1;
	COMPONENT* buttons[4];
	buttons[0] = containerGetComponent(BTN_ROUND);
	buttons[1] = containerGetComponent(BTN_FLAT);
	buttons[2] = containerGetComponent(BTN_OVAL);
	buttons[3] = containerGetComponent(BTN_ROUNDRECT);

	buttonSetFocus(buttons[current], GUI_TRUE);

	while (stop == 0) {
		keysWaitOnPress();
		if (keysGetDown() == 1) {
			buttonSetFocus(buttons[current++], GUI_FALSE);
			if (current == 4) {
				current = 0;
			}

			buttonSetFocus(buttons[current], GUI_TRUE);
		} else if (keysGetUp() == 1) {
			buttonSetFocus(buttons[current--], GUI_FALSE);
			if (current == -1) {
				current = 3;
			}

			buttonSetFocus(buttons[current], GUI_TRUE);
		} else if (keysGetEnter() == 1) {
			switch (current) {
			case 0: // measure
				nextstate = STATE_ROUNDSETTINGS;
				stop = 1;
			break;
			case 1:
				nextstate = STATE_FLATSETTINGS;
				stop=1;
			break;
			case 2:
				nextstate = STATE_OVALSETTINGS;
				stop=1;
			break;
			case 3:
				nextstate = STATE_ROUNDEDRECTSETTINGS;
				stop=1;
			break;
			default:
				nextstate = -1;
				stop = 1;
			}
		}
	}

	return nextstate;
}
