/*
 * spinner.c
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../includes/keys/sapim_keys.h"

#include "../container/container.h"
#include "../component/component.h"
#include "../structs.h"
#include "../functions.h"
#include "spinner.h"

COMPONENT* createSpinner(const char* name, float value, float min, float max,
		float step, short x, short y) {
	SPINNER* spinner = malloc(sizeof(SPINNER));

	spinner->base.id.type = GUI_SPINNER;
	spinner->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(spinner->base.id.name, name, strlen(name) + 1);

	spinner->base.visible = GUI_FALSE;
	spinner->base.focus = GUI_FALSE;

	spinner->deselectedBackground = getDefaultSpinnerBackgroundColor();
	spinner->selectedBackground = getDefaultSpinnerBackgroundSelectedColor();

	spinner->unfocusBorderColor = getDefaultSpinnerBorderColor();
	spinner->focusBorderColor = getDefaultSpinnerBorderFocusColor();

	spinner->triangleColor = getDefaultSpinnerTriangleColor();
	spinner->triangleColorPressed = getDefaultSpinnerTrianglePressedColor();

	spinner->value = value;
	spinner->min = min;
	spinner->max = max;
	spinner->step = step;

	spinner->textColor = GUI_USE_DEFAULT_FOREGROUND_COLOR;
	spinner->font = GUI_USE_DEFAULT_FONT;

	spinner->flags = 0;
	spinner->repaintFlag = SPINNER_REPAINT_ALL;

	spinnerCalculateSize(spinner, &(spinner->base.position.width),
			&(spinner->base.position.height));
	componentSetX((COMPONENT*) spinner, x);
	componentSetY((COMPONENT*) spinner, y);

	containerAddComponent((COMPONENT*) spinner);

	return (COMPONENT*) spinner;
}

void removeSpinner(SPINNER* spinner) {
#if DEBUG > 1
	printf("Debug: Remove spinner\n");
#endif
}

int drawSpinner(SPINNER* spinner) {
	char buff[30];
	short x[3], y[3];
	short yOffsetText;
	int borderColor;
	int backgroundColor;
	int triangleUpColor;
	int triangleDownColor;
	char font = solveFont(spinner->font);

	sprintf(buff, "%1.2f", spinner->value);

	if ((spinner->flags & SPINNER_FOCUS) == 0) {
		borderColor = spinner->unfocusBorderColor;
	} else {
		borderColor = spinner->focusBorderColor;
	}

	if ((spinner->flags & SPINNER_SELECTED) == 0) {
		backgroundColor = spinner->deselectedBackground;
	} else {
		backgroundColor = spinner->selectedBackground;
	}

	if ((spinner->flags & SPINNER_UP) == 0) {
		triangleUpColor = spinner->triangleColor;
	} else {
		triangleUpColor = spinner->triangleColorPressed;
	}

	if ((spinner->flags & SPINNER_DOWN) == 0) {
		triangleDownColor = spinner->triangleColor;
	} else {
		triangleDownColor = spinner->triangleColorPressed;
	}

	if ((spinner->repaintFlag & SPINNER_REPAINT_BORDER)
			== SPINNER_REPAINT_BORDER) {
		setPenType(GUI_PEN_WIRE);
		if (serialDrawRectangle(spinner->base.position.x,
				spinner->base.position.y, spinner->base.position.width,
				spinner->base.position.height, solveColor(borderColor))
				!= GUI_SUCCESS) {
			return GUI_ERROR;
		}
	}

	if ((spinner->repaintFlag & SPINNER_REPAINT_BACKGROUND)
			== SPINNER_REPAINT_BACKGROUND) {
		setPenType(GUI_PEN_SOLID);
		if (serialDrawRectangle(spinner->base.position.x + 1,
				spinner->base.position.y + 1, spinner->base.position.width - 2,
				spinner->base.position.height - 2, solveColor(backgroundColor))
				!= GUI_SUCCESS) {
			return GUI_ERROR;
		}
	}

	if (setTransparant() != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if ((spinner->repaintFlag & SPINNER_REPAINT_TEXT) == SPINNER_REPAINT_TEXT) {
		if ((spinner->repaintFlag & SPINNER_REPAINT_BACKGROUND)
				!= SPINNER_REPAINT_BACKGROUND) {
			setPenType(GUI_PEN_SOLID);

			serialDrawRectangle(spinner->base.position.x + 1,
					spinner->base.position.y + 1, spinner->base.position.width
							- 13, spinner->base.position.height - 2,
					solveColor(backgroundColor));
		}

		if (spinner->base.position.height > calculateCharacterHeight(font)) {
			yOffsetText = (spinner->base.position.height
					- calculateCharacterHeight(font)) / 2;
		} else {
			yOffsetText = 0;
		}

		yOffsetText += spinner->base.position.y;

		if (serialDrawText(spinner->base.position.x + 3, yOffsetText, buff,
				font, solveColor(spinner->textColor)) != GUI_SUCCESS) {
			return GUI_ERROR;
		}
	}

	if ((spinner->repaintFlag & (SPINNER_REPAINT_TIANGLE_UP
			| SPINNER_REPAINT_TRIANGLE_DOWN)) != 0) {
		setPenType(GUI_PEN_SOLID);

		x[0] = spinner->base.position.x + spinner->base.position.width - 7;
		x[1] = spinner->base.position.x + spinner->base.position.width - 13;
		x[2] = spinner->base.position.x + spinner->base.position.width - 1;

		if ((spinner->repaintFlag & SPINNER_REPAINT_TIANGLE_UP)
				== SPINNER_REPAINT_TIANGLE_UP) {
			y[0] = spinner->base.position.y + 1;
			y[1] = (spinner->base.position.height / 2) - 1
					+ spinner->base.position.y;
			y[2] = y[1];

			serialDrawTriangle(x[0], y[0], x[1], y[1], x[2], y[2], solveColor(
					triangleUpColor));
		}

		if ((spinner->repaintFlag & SPINNER_REPAINT_TRIANGLE_DOWN)
				== SPINNER_REPAINT_TRIANGLE_DOWN) {
			y[0] = spinner->base.position.height - 1 + spinner->base.position.y;
			y[1] = spinner->base.position.height
					- ((spinner->base.position.height / 2) - 1)
					+ spinner->base.position.y;
			y[2] = y[1];

			// points of triangle in anti-clockwise
			serialDrawTriangle(x[0], y[0], x[2], y[2], x[1], y[1], solveColor(
					triangleDownColor));
		}
	}

	spinner->repaintFlag = SPINNER_REPAINT_NOTHING;

	return GUI_SUCCESS;
}

void spinnerEnterSelectionMode(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) spinner;
	int count;
	float step = spinnerGetStep(component);
	float stepFast = step * 5.0;

	spinnerSetFocus(component, GUI_TRUE);
	spinnerSetSelected(component, GUI_TRUE);

	keysRefresh();
	keysWaitOnPress();
	while (keysGetEnter() == KEYS_FALSE) {
		if (keysGetUp() == KEYS_TRUE) {
			count = 0;
			spinnerSetStep(component, step);
			spinnerSetUpSelected(component, GUI_TRUE);
			while (keysGetUp() == KEYS_TRUE) {
				spinnerIncValue(component);
				if (count == 0) {
					usleep(350000);
				} else {
					usleep(50000);
				}

				if (count == 10) {
					spinnerSetStep(component, stepFast);
				}
				count++;
				keysRefresh();
			}
			spinnerSetUpSelected(component, GUI_FALSE);
		}

		if (keysGetDown() == KEYS_TRUE) {
			count = 0;
			spinnerSetStep(component, step);
			spinnerSetDownSelected(component, GUI_TRUE);
			while (keysGetDown() == KEYS_TRUE) {
				spinnerDecValue(component);
				if (count == 0) {
					usleep(350000);
				} else {
					usleep(50000);
				}

				if (count == 10) {
					spinnerSetStep(component, stepFast);
				}
				count++;
				keysRefresh();
			}
			spinnerSetDownSelected(component, GUI_FALSE);
		}
		keysWaitOnPress();
	}

	spinnerSetSelected(component, GUI_FALSE);
}

void spinnerCalculateSize(SPINNER* spinner, short *width, short *height) {
	char font = solveFont(spinner->font);
	char text[15];

	sprintf(text, "%1.2f", spinner->value);

	*width = calculateTextWidth(text, font) + 19;
	*height = calculateCharacterHeight(font) + 4;
	if (*height < 25) {
		*height = 25;
	}
}

// setters
void spinnerSetFocus(COMPONENT* component, char focus) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (focus == GUI_TRUE) {
		spinner->flags |= SPINNER_FOCUS;
	} else {
		spinner->flags &= ~SPINNER_FOCUS;
	}

	spinner->repaintFlag |= SPINNER_REPAINT_BORDER;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}
void spinnerSetSelected(COMPONENT* component, char selected) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (selected == GUI_TRUE) {
		spinner->flags |= SPINNER_SELECTED;
	} else {
		spinner->flags &= ~SPINNER_SELECTED;
	}

	spinner->repaintFlag |= SPINNER_REPAINT_BACKGROUND;

	if (visible == GUI_TRUE) {
		componentDraw(component);
	}
}

void spinnerSetUpSelected(COMPONENT* component, char selected) {
	SPINNER* spinner = (SPINNER*) component;
	char isVisible = spinner->base.visible;

	if (selected == GUI_TRUE) {
		spinner->flags |= SPINNER_UP;
	} else {
		spinner->flags &= ~SPINNER_UP;
	}

	spinner->repaintFlag |= SPINNER_REPAINT_TIANGLE_UP;

	if (isVisible == GUI_TRUE) {
		componentDraw(component);
	}
}

void spinnerSetDownSelected(COMPONENT* component, char selected) {
	SPINNER* spinner = (SPINNER*) component;
	char isVisible = spinner->base.visible;

	if (selected == GUI_TRUE) {
		spinner->flags |= SPINNER_DOWN;
	} else {
		spinner->flags &= ~SPINNER_DOWN;
	}
	spinner->repaintFlag |= SPINNER_REPAINT_TRIANGLE_DOWN;

	if (isVisible == GUI_TRUE) {
		componentDraw(component);
	}
}

void spinnerSetValue(COMPONENT* component, float value) {
	SPINNER* spinner = (SPINNER*) component;
	short width, height;
	char isVisible = spinner->base.visible;
	float oldValue = spinner->value;

	if (value > spinner->max) {
		value = spinner->max;
	} else if (value < spinner->min) {
		value = spinner->min;
	}

	if (oldValue != value) {
		spinner->value = value;

		spinnerCalculateSize(spinner, &width, &height);

		if (width != componentGetWidth(component) || height
				!= componentGetHeight(component)) {
			componentHide(component);

			spinner->base.position.width = width;
			spinner->base.position.height = height;

			spinner->repaintFlag |= SPINNER_REPAINT_ALL;
		} else {
			spinner->repaintFlag |= SPINNER_REPAINT_TEXT;
		}

		if (isVisible == GUI_TRUE) {
			componentDraw(component);
		}
	}
}

void spinnerSetMin(COMPONENT* component, float min) {
	SPINNER* spinner = (SPINNER*) component;
	if (spinner->max < min) {
		spinner->max = min;
	}

	spinner->min = min;

	if (spinner->value < spinner->min) {
		spinnerSetValue(component, min);
	}
}

void spinnerSetMax(COMPONENT* component, float max) {
	SPINNER* spinner = (SPINNER*) component;
	if (spinner->min > max) {
		spinner->min = max;
	}

	spinner->max = max;

	if (spinner->value > spinner->max) {
		spinnerSetValue(component, max);
	}
}

void spinnerSetStep(COMPONENT* component, float step) {
	SPINNER* spinner = (SPINNER*) component;

	if (step == 0.0) {
		return;
	}

	spinner->step = step;
}

void spinnerIncValue(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	spinnerSetValue(component, spinnerGetValue(component) + spinner->step);
}

void spinnerDecValue(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	spinnerSetValue(component, spinnerGetValue(component) - spinner->step);
}

// getters
int spinnerGetFocus(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return ((spinner->flags & SPINNER_FOCUS) == 0 ? GUI_FALSE : GUI_TRUE);
}
int spinnerGetSelected(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return ((spinner->flags & SPINNER_SELECTED) == 0 ? GUI_FALSE : GUI_TRUE);
}

int spinnerGetUpSelected(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return ((spinner->flags & SPINNER_UP) == 0 ? GUI_FALSE : GUI_TRUE);
}

int spinnerGetDownSelected(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return ((spinner->flags & SPINNER_DOWN) == 0 ? GUI_FALSE : GUI_TRUE);
}

float spinnerGetValue(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;
	return spinner->value;
}

float spinnerGetMin(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;
	return spinner->min;
}

float spinnerGetMax(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;
	return spinner->max;
}

float spinnerGetStep(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;
	return spinner->step;
}

void spinnerSetForegroundColor(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->textColor != color) {
		spinner->textColor = color;
		spinner->repaintFlag |= SPINNER_REPAINT_TEXT;

		if (visible) {
			componentDraw(component);
		}
	}
}
int spinnerGetForegroundColor(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->textColor;
}

void spinnerSetDeselectedBackground(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->deselectedBackground != color) {
		spinner->deselectedBackground = color;

		if (visible && (spinner->flags & SPINNER_SELECTED) == 0) {
			spinner->repaintFlag |= SPINNER_REPAINT_BACKGROUND;
			componentDraw(component);
		}
	}
}
int spinnerGetDeselectedBackground(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->deselectedBackground;
}

void spinnerSetSelectedBackground(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->selectedBackground != color) {
		spinner->selectedBackground = color;

		if (visible && (spinner->flags & SPINNER_SELECTED) == 1) {
			spinner->repaintFlag |= SPINNER_REPAINT_BACKGROUND;
			componentDraw(component);
		}
	}
}
int spinnerGetSelectedBackground(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->selectedBackground;
}

void spinnerSetFocusBorderColor(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->focusBorderColor != color) {
		spinner->focusBorderColor = color;

		if (visible && (spinner->flags & SPINNER_FOCUS) == 1) {
			spinner->repaintFlag |= SPINNER_REPAINT_BORDER;
			componentDraw(component);
		}
	}
}
int spinnerGetFocusBorderColor(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->focusBorderColor;
}

void spinnerSetUnfocusBorderColor(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->unfocusBorderColor != color) {
		spinner->unfocusBorderColor = color;

		if (visible && (spinner->flags & SPINNER_FOCUS) == 0) {
			spinner->repaintFlag |= SPINNER_REPAINT_BORDER;
			componentDraw(component);
		}
	}
}
int spinnerGetUnfocusBorderColor(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->unfocusBorderColor;
}

void spinnerSetTriangleColor(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->triangleColor != color) {
		spinner->triangleColor = color;

		if (visible && (spinner->flags & SPINNER_DOWN) == 0) {
			spinner->repaintFlag |= SPINNER_REPAINT_TIANGLE_UP
					| SPINNER_REPAINT_TRIANGLE_DOWN;
			componentDraw(component);
		}
	}
}
int spinnerGetTriangleColor(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->triangleColor;
}

void spinnerSetTriangleColorPressed(COMPONENT* component, int color) {
	SPINNER* spinner = (SPINNER*) component;
	char visible = spinner->base.visible;

	if (spinner->triangleColorPressed != color) {
		spinner->triangleColorPressed = color;

		if (visible && (spinner->flags & SPINNER_DOWN) == 1) {
			spinner->repaintFlag |= SPINNER_REPAINT_TIANGLE_UP
					| SPINNER_REPAINT_TRIANGLE_DOWN;
			componentDraw(component);
		}
	}
}
int spinnerGetTriangleColorPressed(COMPONENT* component) {
	SPINNER* spinner = (SPINNER*) component;

	return spinner->triangleColorPressed;
}
