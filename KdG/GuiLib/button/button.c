/*
 * button.c
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#ifdef DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "../component/component.h"
#include "../container/container.h"
#include "../structs.h"
#include "../functions.h"
#include "button.h"

COMPONENT* createButton(const char* name, const char* text, short x, short y) {
	BUTTON* button = malloc(sizeof(BUTTON));

	button->base.id.type = GUI_BUTTON;
	button->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(button->base.id.name, name, strlen(name) + 1);

	button->base.visible = GUI_FALSE;
	button->base.focus = GUI_FALSE;

	button->font = GUI_USE_DEFAULT_FONT;
	button->text = malloc(sizeof(char) * (strlen(text) + 1));
	strncpy(button->text, text, strlen(text) + 1);
	button->textColor = GUI_USE_DEFAULT_FOREGROUND_COLOR;
	button->state = GUI_BTN_UP;
	button->backgroundColor = getDefaultButtonBackgroundColor();
	button->backgroundFocusColor = getDefaultButtonBackgroundFocusColor();

	buttonCalculateSize(button, &(button->base.position.width),
			&(button->base.position.height));
	componentSetX((COMPONENT*) button, x);
	componentSetY((COMPONENT*) button, y);

	containerAddComponent((COMPONENT*) button);

	return (COMPONENT*) button;
}

void removeButton(BUTTON* button) {

#if DEBUG > 1
	printf("Debug: Free text\n");
#endif
	free(button->text);
}

int drawButton(BUTTON* button) {
	char font = solveFont(button->font);
	int backgroundColor;
	int foregroundColor = solveColor(button->textColor);

	if (button->base.focus == GUI_TRUE) {
#if DEBUG > 1
		printf("Debug: backgroundFocus: %08X\n", button->backgroundFocusColor);
#endif
		backgroundColor = solveColor(button->backgroundFocusColor);
	} else {
#if DEBUG > 1
		printf("Debug: background: %08X\n", button->backgroundColor);
#endif
		backgroundColor = solveColor(button->backgroundColor);
	}

	return serialDrawTextButton(button->base.position.x, button->base.position.y,
			button->text, font, foregroundColor, backgroundColor, button->state);
}

void buttonCalculateSize(BUTTON* button, short *width, short *height) {
	char font = solveFont(button->font);

	// the button should be only contain 1 line, so no special calculations are needed
	*width = calculateButtonWidth(button->text, font);
	*height = calculateButtonHeight(font);
}

void buttonSetBackgroundColor(COMPONENT* component, int color) {
	BUTTON* button = (BUTTON*) component;
	char visible = button->base.visible;

	if (button->backgroundColor != color) {
		button->backgroundColor = color;

		if (visible == GUI_TRUE && button->base.focus == GUI_FALSE) {
			componentDraw(component);
		}
	}
}

int buttonGetBackgroundColor(COMPONENT* component) {
	BUTTON* button = (BUTTON*) component;

	return button->backgroundColor;
}

void buttonSetBackgroundFocusColor(COMPONENT* component, int color) {
	BUTTON* button = (BUTTON*) component;
	char visible = button->base.visible;

	if (button->backgroundFocusColor != color) {
		button->backgroundFocusColor = color;

		if (visible == GUI_TRUE && button->base.focus == GUI_TRUE) {
			componentDraw(component);
		}
	}
}

int buttonGetBackgroundFocusColor(COMPONENT* component) {
	BUTTON* button = (BUTTON*) component;

	return button->backgroundFocusColor;
}

void buttonSetState(COMPONENT* component, char state) {
	BUTTON* button = (BUTTON*) component;
	char visible = button->base.visible;

	if (button->state != state) {
		button->state = state;

		if (visible == GUI_TRUE) {
			componentDraw(component);
		}
	}
}
char buttonGetState(COMPONENT* component) {
	BUTTON* button = (BUTTON*) component;

	return button->state;
}

void buttonSetFocus(COMPONENT* component, char focus) {
	BUTTON* button = (BUTTON*) component;
	char visible = button->base.visible;

	if (button->base.focus != focus) {
		button->base.focus = focus;

		if (visible == GUI_TRUE) {
			componentDraw(component);
		}
	}
}

char buttonGetFocus(COMPONENT* component) {
	BUTTON* button = (BUTTON*) component;

	return button->base.focus;
}

