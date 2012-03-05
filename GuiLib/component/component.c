/*
 * guiComponents.c
 *
 *  Created on: May 5, 2011
 *      Author: philip
 */

#ifdef DEBUG_CONTAINER
#include <stdio.h>
#endif

#include <string.h>
#include <stdlib.h>

#include "../../includes/gui/sapim_gui_all.h"
#include "../gui.h"

#include "../container/container.h"
#include "../label/label.h"
#include "../button/button.h"
#include "../spinner/spinner.h"
#include "../circle/circle.h"
#include "../rectangle/rectangle.h"
#include "../oval/oval.h"
#include "../roundrect/roundrect.h"

void privateSetX(COMPONENT* component, short x);
void privateSetY(COMPONENT* component, short y);

void componentRemove(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	componentHide(component);

	if (containerRemoveComponent(base->id.name) == 0) {
		return;
	}

	free(base->id.name);
	base->id.name = 0;

	switch (base->id.type) {
	case GUI_LABEL:
		removeLabel((LABEL*) base);
		break;
	case GUI_BUTTON:
		removeButton((BUTTON*) base);
		break;
	case GUI_SPINNER:
		removeSpinner((SPINNER*) base);
		break;
	case GUI_CIRCLE:
		removeCircle((CIRCLE*) base);
		break;
	case GUI_RECTANGLE:
		removeRectangle((RECTANGLE*) base);
		break;
	case GUI_OVAL:
		removeOval((OVAL*) base);
		break;
	case GUI_ROUNDRECT:
		removeRoundrect((ROUNDRECT*) base);
		break;
	}

	free(base);
}

int componentDraw(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	base->visible = GUI_TRUE;

	switch (base->id.type) {
	case GUI_LABEL:
		return drawLabel((LABEL*) base);
	case GUI_BUTTON:
		return drawButton((BUTTON*) base);
	case GUI_SPINNER:
		return drawSpinner((SPINNER*) base);
	case GUI_CIRCLE:
		return drawCircle((CIRCLE*) base);
	case GUI_OVAL:
		return drawOval((OVAL*) base);
	case GUI_RECTANGLE:
		return drawRectangle((RECTANGLE*) base);
	case GUI_ROUNDRECT:
		return drawRoundrect((ROUNDRECT*) base);
	default:
		return GUI_ERROR;
	}
}

int componentHide(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base->visible == GUI_TRUE) {
		base->visible = GUI_FALSE;

		return clearPart(base->position.x, base->position.y,
				base->position.width, base->position.height);
	} else {
		return GUI_SUCCESS;
	}
}

int componentSetText(COMPONENT* component, const char* text) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;
	char isVisible = base->visible;

	if ((base->id.type & GUI_HAS_TEXT) == 0) {
		return GUI_ERROR_NO_TEXT;
	}

	componentHide((COMPONENT*) base);

	switch (base->id.type) {
	case GUI_LABEL:
		free(((LABEL*) base)->text);
		((LABEL*) base)->text = malloc(sizeof(char) * (strlen(text) + 1));
		strncpy(((LABEL*) base)->text, text, strlen(text) + 1);

		componentCalculateSize(base, &base->position.width,
				&base->position.height);
		break;
	case GUI_BUTTON:
		free(((BUTTON*) base)->text);
		((BUTTON*) base)->text = malloc(sizeof(char) * (strlen(text) + 1));
		strncpy(((BUTTON*) base)->text, text, strlen(text) + 1);

		componentCalculateSize(base, &base->position.width,
				&base->position.height);
		break;
	}

	if (isVisible == GUI_TRUE) {
		componentDraw((COMPONENT*) base);
	}

	return GUI_SUCCESS;
}

int solveColor(int color) {
	switch (color) {
	case GUI_USE_DEFAULT_BACKGROUND_COLOR:
#if DEBUG > 1
		printf("Color solved as background: %08X\n", getBackgroundColor());
#endif
		return getBackgroundColor();
	case GUI_USE_DEFAULT_FOREGROUND_COLOR:
#if DEBUG > 1
		printf("Color solved as foreground: %08X\n", getForegroundColor());
#endif
		return getForegroundColor();
	default:
#if DEBUG > 1
		printf("Color solved as normal color: %08X\n", color);
#endif
		return color;
	}
}

char solveFont(char font) {
	if (font == GUI_USE_DEFAULT_FONT) {
#if DEBUG > 1
		printf("Font solved as default font: %d\n", getDefaultFont());
#endif
		return getDefaultFont();
	} else {
#if DEBUG > 1
		printf("Font solved as %d\n", font);
#endif
		return font;
	}
}

int componentGetWidth(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base == 0) {
		return -1;
	}

	return base->position.width;
}

int componentGetHeight(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base == 0) {
		return -1;
	}

	return base->position.height;
}

void privateSetX(COMPONENT* component, short x) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (x + base->position.width > getDisplayWidth()) {
		x = getDisplayWidth() - base->position.width;
	} else if (x < 0) {
		x = 0;
	}

	base->position.x = x;
}

void componentSetX(COMPONENT* component, short x) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;
	char isVisble = base->visible;

	componentHide(component);

	componentSetLocation(component, x, componentGetY(component));

	if (isVisble == GUI_TRUE) {
		componentDraw(component);
	}
}

short componentGetX(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base == 0) {
		return -1;
	}

	return base->position.x;
}

void privateSetY(COMPONENT* component, short y) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (y + base->position.height > getDisplayHeight()) {
		y = getDisplayHeight() - base->position.height;
	} else if (y < 0) {
		y = 0;
	}

	base->position.y = y;
}

void componentSetY(COMPONENT* component, short y) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;
	char isVisible = base->visible;

	componentHide(component);

	componentSetLocation(component, componentGetX(component), y);

	if (isVisible == GUI_TRUE) {
		componentDraw(component);
	}
}

short componentGetY(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base == 0) {
		return -1;
	}

	return base->position.y;
}

int componentGetRight(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base == 0) {
		return -1;
	}

	return base->position.x + base->position.width;
}

int componentGetBottom(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	if (base == 0) {
		return -1;
	}

	return base->position.y + base->position.height;
}

void componentSetLocation(COMPONENT* component, short x, short y) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;
	char isVisible = base->visible;

	componentHide(component);

	privateSetX(component, x);
	privateSetY(component, y);

	if (isVisible == GUI_TRUE) {
		if (base->id.type == GUI_SPINNER) {
			((SPINNER*) component)->repaintFlag = SPINNER_REPAINT_ALL;
		}
		componentDraw(component);
	}
}

void componentCalculateSize(BASE_COMPONENT* component, short* width,
		short* height) {
	switch (component->id.type) {
	case GUI_LABEL:
		labelCalculateSize((LABEL*) component, width, height);
		break;
	case GUI_BUTTON:
		buttonCalculateSize((BUTTON*) component, width, height);
		break;
	case GUI_SPINNER:
		spinnerCalculateSize((SPINNER*) component, width, height);
		break;
	case GUI_CIRCLE:
		return circleCalculateSize((CIRCLE*) component, width, height);
	default:
		*width = -1;
		*height = -1;
	}
}

const char* componentGetName(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	return base->id.name;
}

void componentSetFont(COMPONENT* component, char font) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;
	char visible = base->visible;

	switch (base->id.type) {
	case GUI_LABEL:
		((LABEL*) base)->font = font;
		break;
	case GUI_BUTTON:
		((BUTTON*) base)->font = font;
		break;
	case GUI_SPINNER:
		((SPINNER*) base)->font = font;
		break;
	default:
		return;
	}

	componentHide(component);

	componentCalculateSize(base, &base->position.width, &base->position.height);

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

char componentGetFont(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	switch (base->id.type) {
	case GUI_LABEL:
		return ((LABEL*) base)->font;
	case GUI_BUTTON:
		return ((BUTTON*) base)->font;
	case GUI_SPINNER:
		return ((SPINNER*) base)->font;
	default:
		return -1;
	}
}

void componentSetForegroundColor(COMPONENT* component, int color) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	switch (base->id.type) {
	case GUI_LABEL:
		((LABEL*) base)->textColor = color;
		break;
	case GUI_BUTTON:
		((BUTTON*) base)->textColor = color;
		break;
	case GUI_SPINNER:
		((SPINNER*) base)->textColor = color;
		break;
	default:
		return;
	}

	if (base->visible == GUI_TRUE) {
#if DEBUG > 1
		printf("Debug: redraw component\n");
#endif
		componentDraw(component);
	}
}

int componentGetForegroundColor(COMPONENT* component) {
	BASE_COMPONENT* base = (BASE_COMPONENT*) component;

	switch (base->id.type) {
	case GUI_LABEL:
		return ((LABEL*) base)->textColor;
	case GUI_BUTTON:
		return ((BUTTON*) base)->textColor;
	case GUI_SPINNER:
		return ((SPINNER*) base)->textColor;
	default:
		return -1;
	}
}
