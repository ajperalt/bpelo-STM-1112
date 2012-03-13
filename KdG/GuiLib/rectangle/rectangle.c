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
#include "rectangle.h"

#include "../../includes/gui/sapim_gui_constants.h"
#include "../../includes/gui/sapim_gui_errors.h"

COMPONENT* createRectangle(const char* name, short x, short y, short width,
		short height, int color, char pen) {
	RECTANGLE* rectangle = malloc(sizeof(RECTANGLE));

	rectangle->base.id.type = GUI_RECTANGLE;
	rectangle->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(rectangle->base.id.name, name, strlen(name) + 1);

	rectangle->base.visible = GUI_FALSE;
	rectangle->base.focus = GUI_FALSE;

	rectangle->base.position.x = x;
	rectangle->base.position.y = y;

	rectangle->base.position.width = width;
	rectangle->base.position.height = height;

	rectangle->color = color;
	rectangle->pen = pen;

	containerAddComponent((COMPONENT*) rectangle);

	return (COMPONENT*) rectangle;
}

void removeRectangle(RECTANGLE* rectangle) {
#if DEBUG > 1
	printf("Debug: Free text\n");
#endif
}

int drawRectangle(RECTANGLE* rectangle) {
	int color = solveColor(rectangle->color);

	if (rectangle->pen == GUI_PEN_WIRE) {
		setPenType(GUI_PEN_WIRE);
	} else {
		setPenType(GUI_PEN_SOLID);
	}

	serialDrawRectangle(rectangle->base.position.x, rectangle->base.position.y,
			rectangle->base.position.width, rectangle->base.position.height,
			color);

	// always go back to PEN_WIRE, it is the most used (in labels etc)
	setPenType(GUI_PEN_WIRE);

	return GUI_SUCCESS;;
}

void rectangleCalculateSize(RECTANGLE* rectangle, short *width, short *height) {
	*width = rectangle->base.position.width;
	*height = rectangle->base.position.height;
}

void rectangleSetColor(COMPONENT* component, int rgb) {
	RECTANGLE *rectangle = (RECTANGLE*) component;

	rectangle->color = rgb;
}

int rectangleGetColor(COMPONENT* component) {
	RECTANGLE *rectangle = (RECTANGLE*) component;

	return rectangle->color;
}

void rectangleSetPenType(COMPONENT* component, char type) {
	RECTANGLE *rectangle = (RECTANGLE*) component;

	rectangle->pen = type;
}

int rectangleGetPenType(COMPONENT* component) {
	RECTANGLE *rectangle = (RECTANGLE*) component;

	return rectangle->pen;
}

void rectangleSetWidth(COMPONENT* component, short width) {
	RECTANGLE *rectangle = (RECTANGLE*) component;
	char visible = rectangle->base.visible;

	componentHide(component);

	rectangle->base.position.width = width;

	if(visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int circleGetWidth(COMPONENT* component) {
	RECTANGLE *rectangle = (RECTANGLE*) component;

	return rectangle->base.position.width;
}

void rectangleSetHeight(COMPONENT* component, short height) {
	RECTANGLE *rectangle = (RECTANGLE*) component;
	char visible = rectangle->base.visible;

	componentHide(component);

	rectangle->base.position.height = height;

	if(visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int circleGetHeight(COMPONENT* component) {
	RECTANGLE *rectangle = (RECTANGLE*) component;

	return rectangle->base.position.height;
}
