/*
 * guiParameters.c
 *
 *  Created on: May 5, 2011
 *      Author: philip
 */

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#include "gui.h"

#include "../includes/serial/sapim_serial_all.h"
#include "../includes/gui/sapim_gui_errors.h"
#include "../includes/gui/sapim_gui_constants.h"
#include "../includes/gui/sapim_gui_functions.h"

// colors
int backgroundColor = -1;
int foregroundColor = -1;

int buttonBackgroundColor = -1;
int buttonForegroundColor = -1;
int buttonBackgroundFocusColor = -1;

int spinnerBackgroundColor = -1;
int spinnerBackgroundSelectedColor = -1;
int spinnerForegroundColor = -1;
int spinnerBorderColor = -1;
int spinnerBorderFocusColor = -1;
int spinnerTriangleColor = -1;
int spinnerTrianglePressedColor = -1;

// font types
char textFont = -1;

// pentype
char penType = -1;

// text background transparancy
int transparant = -1;

int guiInit(void) {
	if (setBackgroundColor(GUI_BACKGROUND) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setForegroundColor(GUI_FOREGROUND) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultFont(GUI_FONT) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setPenType(GUI_PEN) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setTransparant() != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultButtonBackgroundColor(GUI_BUTTON_BACKGROUND) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultButtonBackgroundFocusColor(GUI_BUTTON_BACKGROUND_FOCUS) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultButtonForegroundColor(GUI_BUTTON_FOREGROUND) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultSpinnerBackgroundColor(GUI_SPINNER_BACKGROUND) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultSpinnerBackgroundSelectedColor(GUI_SPINNER_BACKGROUND_SELECTED) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultSpinnerBorderColor(GUI_SPINNER_BORDER) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultSpinnerBorderFocusColor(GUI_SPINNER_BORDER_FOCUS) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultSpinnerTriangleColor(GUI_SPINNER_TRIANGLE) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultSpinnerTrianglePressedColor(GUI_SPINNER_TRIANGLE_PRESSED) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setDefaultspinnerForegroundColor(GUI_SPINNER_FOREGROUND) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (clearScreen() != GUI_SUCCESS) {
		return GUI_ERROR;
	}

#if DEBUG > 1
	printf("Debug: init success\n");
#endif
	return GUI_SUCCESS;
}

int replaceBackgroundColor(int rgb) {
	char cmd[3];
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x42;
	cmd[1] = color >> 8;
	cmd[2] = (char) (color & 0x00FF);

	if (serialWriteData(cmd, 3, 1) != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't change the background!\n");
#endif
		return GUI_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: Backgroundcolor changed!\n");
#endif
		backgroundColor = rgb;
		return GUI_SUCCESS;
	}
}

int setBackgroundColor(int rgb) {
	char cmd[3];
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x4B;
	cmd[1] = color >> 8;
	cmd[2] = (char) (color & 0x00FF);

	if (serialWriteData(cmd, 3, 1) != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't change the background!\n");
#endif
		return GUI_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: Backgroundcolor changed!\n");
#endif
		backgroundColor = rgb;
		return GUI_SUCCESS;
	}
}


// solid of wire-frame
int setPenType(char type) {
	char cmd[2];

	// no need to change...
	if (type == penType) {
		return GUI_SUCCESS;
	}

	cmd[0] = 0x70;
	cmd[1] = type;
	if (serialWriteData(cmd, 2, 1) != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't change the pen type!\n");
#endif
		return GUI_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: pen type changed!\n");
#endif
		penType = type;
		return GUI_SUCCESS;
	}
}
// stel een font in
int setDefaultFont(char size) {
	textFont = size;
	return GUI_SUCCESS;
}

// maak de achtergrond van tekst transparant
int setTransparant(void) {
	char cmd[2];

	if (transparant == GUI_TRUE) {
		return GUI_SUCCESS;
	}

	cmd[0] = 0x4F;
	cmd[1] = 0x00;
	if (serialWriteData(cmd, 2, 1) != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't set transparant!\n");
#endif
		return GUI_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: transparant set!\n");
#endif
		transparant = GUI_TRUE;
		return GUI_SUCCESS;
	}
}
// maak de achtergrond van de tekst dezelfde als de achtergrondkleur
int setOpaque(void) {
	char cmd[2];

	if (transparant == GUI_FALSE) {
		return GUI_SUCCESS;
	}

	cmd[0] = 0x4F;
	cmd[1] = 0x01;
	if (serialWriteData(cmd, 2, 1) != SERIAL_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't change opaque!\n");
#endif
		return GUI_ERROR;
	} else {
#if DEBUG > 1
		printf("Debug: opaque set!\n");
#endif
		transparant = GUI_FALSE;
		return GUI_SUCCESS;
	}
}
// stel een standaard tekstkleur in
int setForegroundColor(int rgb) {
	if (foregroundColor == rgb) {
		return GUI_SUCCESS;
	} else {
		foregroundColor = rgb;
		return GUI_SUCCESS;
	}
}

char getDefaultFont() {
	return textFont;
}

char getPenType() {
	return penType;
}

int getTransparant() {
	return transparant;
}

int getOpaque() {
	return (transparant == GUI_TRUE ? GUI_FALSE : GUI_TRUE);
}

int getForegroundColor() {
	return foregroundColor;
}

int getBackgroundColor() {
	return backgroundColor;
}

/*
 * button properties
 */
int setDefaultButtonBackgroundColor(int color) {
	buttonBackgroundColor = color;
	return GUI_SUCCESS;
}
int getDefaultButtonBackgroundColor() {
	return buttonBackgroundColor;
}

int setDefaultButtonForegroundColor(int color) {
	buttonForegroundColor = color;
	return GUI_SUCCESS;
}

int getDefaultButtonForegroundColor() {
	return buttonForegroundColor;
}

int setDefaultButtonBackgroundFocusColor(int color) {
	buttonBackgroundFocusColor = color;
	return GUI_SUCCESS;
}

int getDefaultButtonBackgroundFocusColor() {
	return buttonBackgroundFocusColor;
}

/*
 * spinner properties
 */
int setDefaultSpinnerBackgroundColor(int color) {
	spinnerBackgroundColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerBackgroundColor() {
	return spinnerBackgroundColor;
}

int setDefaultSpinnerBackgroundSelectedColor(int color) {
	spinnerBackgroundSelectedColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerBackgroundSelectedColor() {
	return spinnerBackgroundSelectedColor;

}

int setDefaultspinnerForegroundColor(int color) {
	spinnerForegroundColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerForegroundColor() {
	return spinnerForegroundColor;

}

int setDefaultSpinnerBorderColor(int color) {
	spinnerBorderColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerBorderColor() {
	return spinnerBorderColor;

}

int setDefaultSpinnerBorderFocusColor(int color) {
	spinnerBorderFocusColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerBorderFocusColor() {
	return spinnerBorderFocusColor;

}

int setDefaultSpinnerTriangleColor(int color) {
	spinnerTriangleColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerTriangleColor() {
	return spinnerTriangleColor;

}

int setDefaultSpinnerTrianglePressedColor(int color) {
	spinnerTrianglePressedColor = color;
	return GUI_SUCCESS;
}

int getDefaultSpinnerTrianglePressedColor() {
	return spinnerTrianglePressedColor;
}

