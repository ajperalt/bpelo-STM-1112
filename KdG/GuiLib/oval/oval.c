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
#include "oval.h"

#include "../../includes/gui/sapim_gui_constants.h"
#include "../../includes/gui/sapim_gui_errors.h"

COMPONENT* createOval(const char* name, short x, short y, short radiusX,
		short radiusY, int color, char pen) {
	OVAL* oval = malloc(sizeof(OVAL));

	oval->base.id.type = GUI_OVAL;
	oval->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(oval->base.id.name, name, strlen(name) + 1);

	oval->base.visible = GUI_FALSE;
	oval->base.focus = GUI_FALSE;

	oval->base.position.x = x;
	oval->base.position.y = y;

	oval->radiusX = radiusX;
	oval->radiusY = radiusY;
	oval->color = color;
	oval->pen = pen;

	ovalCalculateSize(oval, &oval->base.position.width,
			&oval->base.position.height);

	containerAddComponent((COMPONENT*) oval);

	return (COMPONENT*) oval;
}

void removeOval(OVAL* circle) {
#if DEBUG > 1
	printf("Debug: Free text\n");
#endif
}

int drawOval(OVAL* oval) {
	int color = solveColor(oval->color);
	int x = oval->base.position.x + oval->base.position.width / 2;
	int y = oval->base.position.y + oval->base.position.height / 2;

	if (oval->pen == GUI_PEN_WIRE) {
		setPenType(GUI_PEN_WIRE);
	} else {
		setPenType(GUI_PEN_SOLID);
	}

	serialDrawElipse(x, y, oval->radiusX, oval->radiusY, color);

	// always go back to PEN_WIRE, it is the most used (in labels etc)
	setPenType(GUI_PEN_WIRE);

	return GUI_SUCCESS;;
}

void ovalCalculateSize(OVAL* oval, short *width, short *height) {
	*width = oval->radiusX * 2;
	*height = oval->radiusY * 2;
}

void ovalSetColor(COMPONENT* component, int rgb) {
	OVAL *oval = (OVAL*) component;

	oval->color = rgb;
}

int ovalGetColor(COMPONENT* component) {
	OVAL *oval = (OVAL*) component;

	return oval->color;
}

void ovalSetPenType(COMPONENT* component, char type) {
	OVAL *oval = (OVAL*) component;

	oval->pen = type;
}

int ovalGetPenType(COMPONENT* component) {
	OVAL *oval = (OVAL*) component;

	return oval->pen;
}

void ovalSetRadiusX(COMPONENT* component, short radius) {
	OVAL *oval = (OVAL*) component;
	char visible = oval->base.visible;

	componentHide(component);

	oval->radiusX = radius;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int ovalGetRadiusX(COMPONENT* component) {
	OVAL *oval = (OVAL*) component;

	return oval->radiusX;
}

void ovalSetRadiusY(COMPONENT* component, short radius) {
	OVAL *oval = (OVAL*) component;
	char visible = oval->base.visible;

	componentHide(component);

	oval->radiusY = radius;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

int ovalGetRadiusY(COMPONENT* component) {
	OVAL *oval = (OVAL*) component;

	return oval->radiusY;
}
