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
#include "circle.h"

#include "../../includes/gui/sapim_gui_constants.h"
#include "../../includes/gui/sapim_gui_errors.h"

COMPONENT* createCircle(const char* name, short x, short y, short radius,
		int color, char pen) {
	CIRCLE* circle = malloc(sizeof(CIRCLE));

	circle->base.id.type = GUI_CIRCLE;
	circle->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(circle->base.id.name, name, strlen(name) + 1);

	circle->base.visible = GUI_FALSE;
	circle->base.focus = GUI_FALSE;

	circle->base.position.x = x;
	circle->base.position.y = y;

	circle->radius = radius;
	circle->color = color;
	circle->pen = pen;

	circleCalculateSize(circle, &circle->base.position.width,
			&circle->base.position.height);

	containerAddComponent((COMPONENT*) circle);

	return (COMPONENT*) circle;
}

void removeCircle(CIRCLE* circle) {
#if DEBUG > 1
	printf("Debug: Free text\n");
#endif
}

int drawCircle(CIRCLE* circle) {
	int color = solveColor(circle->color);
	int x = circle->base.position.x + circle->base.position.width / 2;
	int y = circle->base.position.y + circle->base.position.height / 2;

	if (circle->pen == GUI_PEN_WIRE) {
		setPenType(GUI_PEN_WIRE);
	} else {
		setPenType(GUI_PEN_SOLID);
	}

	serialDrawCircle(x, y, circle->radius, color);

	// always go back to PEN_WIRE, it is the most used (in labels etc)
	setPenType(GUI_PEN_WIRE);

	return GUI_SUCCESS;;
}

void circleCalculateSize(CIRCLE* circle, short *width, short *height) {
	*width = circle->radius * 2;
	*height = *width;
}

void circleSetColor(COMPONENT* component, int rgb) {
	CIRCLE *circle = (CIRCLE*) component;

	circle->color = rgb;
}

int circleGetColor(COMPONENT* component) {
	CIRCLE *circle = (CIRCLE*) component;

	return circle->color;
}

void circleSetPenType(COMPONENT* component, char type) {
	CIRCLE *circle = (CIRCLE*) component;

	circle->pen = type;
}

int circleGetPenType(COMPONENT* component) {
	CIRCLE *circle = (CIRCLE*) component;

	return circle->pen;
}

void circleSetRadius(COMPONENT* component, short radius) {
	CIRCLE *circle = (CIRCLE*) component;
	char visible = circle->base.visible;

	componentHide(component);

	circle->radius = radius;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int circleGetRadius(COMPONENT* component) {
	CIRCLE *circle = (CIRCLE*) component;

	return circle->radius;
}
