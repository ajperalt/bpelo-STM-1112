/*
 * circle.c
 *
 *  Created on: May 19, 2011
 *      Author: philip
 */

#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../component/component.h"
#include "../container/container.h"
#include "../structs.h"
#include "../functions.h"
#include "roundrect.h"

#include "../../includes/gui/sapim_gui_constants.h"
#include "../../includes/gui/sapim_gui_errors.h"

COMPONENT* createRoundrect(const char* name, short x, short y,
		short outerWidth, short innerWidth, short height, int color, char pen) {
	ROUNDRECT* roundrect = malloc(sizeof(ROUNDRECT));

	roundrect->base.id.type = GUI_ROUNDRECT;
	roundrect->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(roundrect->base.id.name, name, strlen(name) + 1);

	roundrect->base.visible = GUI_FALSE;
	roundrect->base.focus = GUI_FALSE;

	roundrect->base.position.x = x;
	roundrect->base.position.y = y;

	roundrect->outerWidth = outerWidth;
	roundrect->innerWidth = innerWidth;
	roundrect->height = height;
	roundrect->color = color;
	roundrect->pen = pen;

	roundrectCalculateSize(roundrect, &roundrect->base.position.width,
			&roundrect->base.position.height);

	containerAddComponent((COMPONENT*) roundrect);

	return (COMPONENT*) roundrect;
}

void removeRoundrect(ROUNDRECT* roundrect) {
#if DEBUG > 1
	printf("Debug: Free text\n");
#endif
}

int drawRoundrect(ROUNDRECT* roundrect) {
	int color = solveColor(roundrect->color);
	int x = roundrect->base.position.x;
	int y = roundrect->base.position.y;
	int xOval = roundrect->base.position.x + roundrect->base.position.width / 2;
	int yOval = roundrect->base.position.y + roundrect->base.position.height
			/ 2;
	int rectWidth = (roundrect->outerWidth - roundrect->innerWidth) / 2;

	if (roundrect->pen == GUI_PEN_WIRE) {
		setPenType(GUI_PEN_WIRE);
	} else {
		setPenType(GUI_PEN_SOLID);
	}

	serialDrawElipse(xOval, yOval, roundrect->outerWidth / 2, roundrect->height
			/ 2, color);
	serialDrawRectangle(x, y, rectWidth, roundrect->height,
			getBackgroundColor());
	serialDrawRectangle(x + roundrect->innerWidth + rectWidth, y, rectWidth,
			roundrect->height, getBackgroundColor());

	// always go back to PEN_WIRE, it is the most used (in labels etc)
	setPenType(GUI_PEN_WIRE);

	return GUI_SUCCESS;;
}

void roundrectCalculateSize(ROUNDRECT* roundrect, short *width, short *height) {
	*width = roundrect->outerWidth;
	*height = roundrect->height;
}

void roundrectSetColor(COMPONENT* component, int rgb) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	roundrect->color = rgb;
}

int roundrectGetColor(COMPONENT* component) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	return roundrect->color;
}

void roundrectSetPenType(COMPONENT* component, char type) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	roundrect->pen = type;
}

int roundrectGetPenType(COMPONENT* component) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	return roundrect->pen;
}

void roundrectSetOuterWidth(COMPONENT* component, short width) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;
	char visible = roundrect->base.visible;

	componentHide(component);

	roundrect->outerWidth = width;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int roundrectGetOuterWidth(COMPONENT* component) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	return roundrect->outerWidth;
}

void roundrectSetInnerWidth(COMPONENT* component, short width) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;
	char visible = roundrect->base.visible;

	componentHide(component);

	roundrect->innerWidth = width;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int roundrectGetInnerWidth(COMPONENT* component) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	return roundrect->innerWidth;
}

void roundrectSetWidth(COMPONENT* component, short height) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;
	char visible = roundrect->base.visible;

	componentHide(component);

	roundrect->height = height;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int roundrectGetHeight(COMPONENT* component) {
	ROUNDRECT *roundrect = (ROUNDRECT*) component;

	return roundrect->height;
}
