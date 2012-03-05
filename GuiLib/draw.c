/*
 * gui.c
 *
 *  Created on: May 4, 2011
 *      Author: philip
 */

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#include <string.h>

#include "../SerialLib/serial.h"
#include "gui.h"

#include "../includes/gui/sapim_gui_all.h"
#include "../includes/serial/sapim_serial_errors.h"
#include "../includes/serial/sapim_serial_functions.h"

// bepaal de teksthoogte met de ingestelde font met "setFont"
int calculateTextHeight(const char* text, char font) {
	return calculateCharacterHeight(font);
}

// bepaal de breedte van de tekst met de standaard font, ingesteld via "setFont"
int calculateTextWidth(const char* text, char font) {
	int strLen = strlen(text);

	return strLen * calculateCharacterWidth(font);
}
// bepaal de breedte van 1 karakter met de standaard font, ingesteld via "setFont"
int calculateCharacterWidth(char font) {
	switch (font) {
	case GUI_FONT_SMALL:
		return 5;
	case GUI_FONT_MEDIUM:
		return 8;
	case GUI_FONT_LARGE:
		return 8;
	case GUI_FONT_LARGEST:
		return 12;
	default:
		return GUI_ERROR;
	}
}

int calculateCharacterHeight(char font) {
	switch (font) {
	case GUI_FONT_SMALL:
		return 7;
	case GUI_FONT_MEDIUM:
		return 8;
	case GUI_FONT_LARGE:
		return 12;
	case GUI_FONT_LARGEST:
		return 16;
	default:
		return GUI_ERROR;
	}
}

int calculateButtonHeight(char font) {
	switch (font) {
	case GUI_FONT_SMALL:
		return 7 + 9;
	case GUI_FONT_MEDIUM:
		return 8 + 8;
	case GUI_FONT_LARGE:
		return 12 + 8;
	case GUI_FONT_LARGEST:
		return 16 + 8;
	default:
		return GUI_ERROR;
	}
}

int calculateButtonWidth(const char* text, char font) {
	int width = calculateTextWidth(text, font);
	switch (font) {
	case GUI_FONT_SMALL:
		return width + 22;
	case GUI_FONT_MEDIUM:
		return width + 9;
	case GUI_FONT_LARGE:
		return width + 9;
	case GUI_FONT_LARGEST:
		return width + 9;
	default:
		return GUI_ERROR;
	}
}


int getDisplayWidth() {
	return 320;
}

int getDisplayHeight() {
	return 240;
}

/*
 * omzet functies om met rij/kolom indexes te kunnen werken, nodig want alle functies werken met pixels
 * en niet met kolom/rij indexes
 */
int convertRowToPixels(char row, char font) {
	return (row * calculateCharacterHeight(font));
}

int convertColumnToPixels(char column, char font) {
	return (column * calculateCharacterWidth(font));
}

/*
 * clear screen functies
 */
int clearScreen(void) {
	char cmd = 0x45;

	if (serialWriteData(&cmd, sizeof(cmd), 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't clear the screen\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}
/*
 * cleart een deel van het scherm
 */
int clearPart(int x, int y, int width, int height) {
	char oldPen = getPenType();

	if (setPenType(GUI_PEN_SOLID) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (serialDrawRectangle(x, y, width, height, getBackgroundColor()) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

	if (setPenType(oldPen) != GUI_SUCCESS) {
		return GUI_ERROR_RESTORE_SETTINGS;
	}

	return GUI_SUCCESS;
}
/*
 * "hertekent" de tekst, maar met de achtergrondkleur; effect: text wordt verwijdert
 */
int clearText(int x, int y, const char* str, char font) {
	return clearPart(x, y, calculateTextWidth(str, font), calculateTextHeight(
			str, font));
}

// teken een tekst op positie (x,y) in pixels, met de standaard font en textkleur
int serialDrawText(short x, short y, const char* str, char font, int color) {
	char cmd[257]; // 257 is the max size of a text command
	short textColor = convertRGB24to5R6G5B(color);

	cmd[0] = 0x53;
	cmd[1] = (char) (x >> 8);
	cmd[2] = (char) (x & 0xFF);
	cmd[3] = (char) (y >> 8);
	cmd[4] = (char) (y & 0xFF);
	cmd[5] = font;
	cmd[6] = (char) (textColor >> 8);
	cmd[7] = (char) (textColor & 0xFF);
	cmd[8] = 1;
	cmd[9] = 1;
	strncpy(cmd + 10, str, strlen(str) + 1);

	if (serialWriteData(cmd, strlen(str) + 11, 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the text\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}

// teken een knop met de standaard tekstkleur en font
int serialDrawTextButton(short x, short y, const char* str, char font, int color,
		int rgbBtn, char state) {
	char cmd[257]; // 257 is the max size of a text command
	short textColor = convertRGB24to5R6G5B(color);
	short buttonColor = convertRGB24to5R6G5B(rgbBtn);

	cmd[0] = 0x62;
	cmd[1] = state;
	cmd[2] = (char) (x >> 8);
	cmd[3] = (char) (x & 0xFF);
	cmd[4] = (char) (y >> 8);
	cmd[5] = (char) (y & 0xFF);
	cmd[6] = (char) (buttonColor >> 8);
	cmd[7] = (char) (buttonColor & 0xFF);
	cmd[8] = font;
	cmd[9] = (char) (textColor >> 8);
	cmd[10] = (char) (textColor & 0xFF);
	cmd[11] = 1;
	cmd[12] = 1;
	strncpy(cmd + 13, str, strlen(str) + 1);

	if (serialWriteData(cmd, strlen(str) + 14, 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the text button\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}

// teken een cirkel, (x,y) = center in px
int serialDrawCircle(short x, short y, short radius, int rgb) {
	char cmd[9]; // 257 is the max size of a text command
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x43;
	cmd[1] = (char) (x >> 8);
	cmd[2] = (char) (x & 0xFF);
	cmd[3] = (char) (y >> 8);
	cmd[4] = (char) (y & 0xFF);
	cmd[5] = (char) (radius >> 8);
	cmd[6] = (char) (radius & 0xFF);
	cmd[7] = (char) (color >> 8);
	cmd[8] = (char) (color & 0xFF);

	if (serialWriteData(cmd, sizeof(cmd), 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the circle\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}

// teken elipse: (x, y) = center in pixels
int serialDrawElipse(short x, short y, short xRadius, short yRadius, int rgb) {
	char cmd[11]; // 257 is the max size of a text command
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x65;
	cmd[1] = (char) (x >> 8);
	cmd[2] = (char) (x & 0xFF);
	cmd[3] = (char) (y >> 8);
	cmd[4] = (char) (y & 0xFF);
	cmd[5] = (char) (xRadius >> 8);
	cmd[6] = (char) (xRadius & 0xFF);
	cmd[7] = (char) (yRadius >> 8);
	cmd[8] = (char) (yRadius & 0xFF);
	cmd[9] = (char) (color >> 8);
	cmd[10] = (char) (color & 0xFF);

	if (serialWriteData(cmd, sizeof(cmd), 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the elipse\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}
// teken een driehoek. punten in tegenwijzerzin!!
int serialDrawTriangle(short x1, short y1, short x2, short y2, short x3, short y3,
		int rgb) {
	char cmd[15]; // 257 is the max size of a text command
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x47;
	cmd[1] = (char) (x1 >> 8);
	cmd[2] = (char) (x1 & 0xFF);
	cmd[3] = (char) (y1 >> 8);
	cmd[4] = (char) (y1 & 0xFF);

	cmd[5] = (char) (x2 >> 8);
	cmd[6] = (char) (x2 & 0xFF);
	cmd[7] = (char) (y2 >> 8);
	cmd[8] = (char) (y2 & 0xFF);

	cmd[9] = (char) (x3 >> 8);
	cmd[10] = (char) (x3 & 0xFF);
	cmd[11] = (char) (y3 >> 8);
	cmd[12] = (char) (y3 & 0xFF);

	cmd[13] = (char) (color >> 8);
	cmd[14] = (char) (color & 0xFF);

	if (serialWriteData(cmd, sizeof(cmd), 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the triangle\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}

// teken een lijn
int serialDrawLine(short x1, short y1, short x2, short y2, int rgb) {
	char cmd[11]; // 257 is the max size of a text command
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x4C;
	cmd[1] = (char) (x1 >> 8);
	cmd[2] = (char) (x1 & 0xFF);
	cmd[3] = (char) (y1 >> 8);
	cmd[4] = (char) (y1 & 0xFF);

	cmd[5] = (char) (x2 >> 8);
	cmd[6] = (char) (x2 & 0xFF);
	cmd[7] = (char) (y2 >> 8);
	cmd[8] = (char) (y2 & 0xFF);

	cmd[9] = (char) (color >> 8);
	cmd[10] = (char) (color & 0xFF);

	if (serialWriteData(cmd, sizeof(cmd), 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the triangle\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}

// teken een vierkant
int serialDrawRectangle(short x, short y, short width, short height, int rgb) {
	char cmd[11]; // 257 is the max size of a text command
	short color = convertRGB24to5R6G5B(rgb);

	cmd[0] = 0x72;
	cmd[1] = (char) (x >> 8);
	cmd[2] = (char) (x & 0xFF);
	cmd[3] = (char) (y >> 8);
	cmd[4] = (char) (y & 0xFF);
	cmd[5] = (char) ((x + width) >> 8);
	cmd[6] = (char) ((x + width) & 0xFF);
	cmd[7] = (char) ((y + height) >> 8);
	cmd[8] = (char) ((y + height) & 0xFF);
	cmd[9] = (char) (color >> 8);
	cmd[10] = (char) (color & 0xFF);

	if (serialWriteData(cmd, 11, 1) != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: Couldn't draw the rectangle\n");
#endif
		return GUI_ERROR;
	} else {
		return GUI_SUCCESS;
	}
}

short convertRGB24to5R6G5B(int rgb24) {
	return (short) (((rgb24 >> 8) & 0x0000F800) | ((rgb24 >> 5) & 0x00007E0)
			| ((rgb24 >> 3) & 0x0000001F));
}

