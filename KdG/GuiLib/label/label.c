/*
 * label.c
 *
 *  Created on: May 7, 2011
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
#include "label.h"

COMPONENT* createLabel(const char* name, const char* text, short x, short y) {
	LABEL* label = malloc(sizeof(LABEL));

	label->base.id.type = GUI_LABEL;
	label->base.id.name = malloc(sizeof(char) * (strlen(name) + 1));
	strncpy(label->base.id.name, name, strlen(name) + 1);

	label->base.visible = GUI_FALSE;
	label->base.focus = GUI_FALSE;

	label->font = GUI_USE_DEFAULT_FONT;
	label->text = malloc(sizeof(char) * (strlen(text) + 1));
	strncpy(label->text, text, strlen(text) + 1);
	label->textColor = GUI_USE_DEFAULT_FOREGROUND_COLOR;
	label->transparant = GUI_TRUE;
	label->backgroundColor = GUI_USE_DEFAULT_BACKGROUND_COLOR;
	label->borderColor = GUI_USE_DEFAULT_BACKGROUND_COLOR;

	if (x < getDisplayWidth() - calculateCharacterWidth(solveFont(label->font))) {
		label->base.position.x = x;
	} else {
		label->base.position.x = x - calculateCharacterWidth(solveFont(
				label->font));
	}

	if (y < getDisplayHeight() - calculateCharacterHeight(
			solveFont(label->font))) {
		label->base.position.y = y;
	} else {
		label->base.position.y = y - calculateCharacterHeight(solveFont(
				label->font));
	}

	labelCalculateSize(label, &(label->base.position.width),
			&(label->base.position.height));

	containerAddComponent((COMPONENT*) label);

	return (COMPONENT*) label;
}

void removeLabel(LABEL* label) {
#if DEBUG > 1
	printf("Debug: Free text\n");
#endif
	free(label->text);
}

int drawLabel(LABEL* label) {
	char font = solveFont(label->font);
	int color = solveColor(label->textColor);
	int backgroundColor = solveColor(label->backgroundColor);
	int borderColor = solveColor(label->borderColor);
	char* buff = 0;
	short lineWidth = label->base.position.width;
	int charsPerLine = lineWidth / calculateCharacterWidth(font);
	int strLen = strlen(label->text);
	int lineCount = strLen / charsPerLine;
	int i;
	int success = 1;

	if (lineCount * charsPerLine < strLen) {
		lineCount++;
	}

	if (setTransparant() != GUI_SUCCESS) {
#ifdef DEBUG
		printf("Error: drawLabel: transparant\n");
#endif
		return GUI_ERROR;
	}

	if (label->transparant == GUI_FALSE) {
		setPenType(GUI_PEN_SOLID);
		if (serialDrawRectangle(label->base.position.x, label->base.position.y,
				label->base.position.width, label->base.position.height,
				backgroundColor) != GUI_SUCCESS) {
			return GUI_ERROR;
		}
	}

	setPenType(GUI_PEN_WIRE);
	if (serialDrawRectangle(label->base.position.x, label->base.position.y,
			label->base.position.width, label->base.position.height,
			borderColor) != GUI_SUCCESS) {
		return GUI_ERROR;
	}

#if DEBUG > 1
	printf("Debug: writing %d lines of %d chars; linewidth: %d\n", lineCount,
			charsPerLine, lineWidth);
#endif
	buff = (char*) malloc(sizeof(char) * (charsPerLine + 1));
	for (i = 0; i < lineCount; i++) {
		strncpy(buff, label->text + (i * charsPerLine), charsPerLine);
		buff[charsPerLine] = '\0';

		if (serialDrawText(label->base.position.x + 2, label->base.position.y + (i
				* calculateCharacterHeight(font)) + 2, buff, font, color)
				!= GUI_SUCCESS) {
			success = 0;
		}
	}

	return (success == 1 ? GUI_SUCCESS : GUI_ERROR);
}

void labelCalculateSize(LABEL* label, short *width, short *height) {
	char font = solveFont(label->font);
	short xWidth = getDisplayWidth() - label->base.position.x;
#if DEBUG > 1
	printf("Debug: calculating labelsize; xWidth: %d\n", xWidth);
#endif

	*width = calculateTextWidth(label->text, font) + 4;
#if DEBUG > 1
	printf("Debug: calculating text width: %d\n", *width);
#endif

	if (*width > xWidth) {
		*height = (*width / xWidth);
		if (*height * xWidth < *width) {
			(*height)++;
		}

		*height = *height * calculateCharacterHeight(font);
		*width = xWidth - 4;
	} else {
		*height = calculateCharacterHeight(font);
	}

	*height += 4;
}

void labelWordWrap(COMPONENT* component) {
	LABEL* label = (LABEL*) component; // convert to label
	char font = solveFont(label->font); // get the font
	short lineWidth = label->base.position.width; // get the width of the label
	int charsPerLine = lineWidth / calculateCharacterWidth(font); // determine the amount of characters per line
	int strLen = strlen(label->text); // total length of the string

	char buff[MAX_LABEL_LENGTH + 1]; // buffer to allocate new string
	int buffIndex = 0;

	char removeSpace = GUI_TRUE; // extra spaces are getting removed
	int i;
	int startWord, endWord;
	char* str = label->text; // pointer to the text of the label
	int charsAvailable = charsPerLine;
	int wordLength = 0;

	startWord = endWord = 0;
	for (i = 0; i <= strLen; i++) {
		if ((str[i] == ' ' || str[i] == '\0') && removeSpace == GUI_FALSE) {
			endWord = i - 1;
#if DEBUG > 1
			printf("Debug: End word: %d\n", endWord);
#endif
			removeSpace = GUI_TRUE;
		} else if (str[i] != ' ' && removeSpace == GUI_TRUE) {
			startWord = i;
#if DEBUG > 1
			printf("Debug: Start word: %d\n", startWord);
#endif
			removeSpace = GUI_FALSE;
		}

		// new word found!
		if (startWord < endWord) {
			wordLength = endWord - startWord + 1;
#if DEBUG > 1
			printf(
					"Debug: Word length: %d; charsAvailable: %d; charsPerLine: %d\n",
					wordLength, charsAvailable, charsPerLine);
			printf("Debug: buffIndex: %d\n", buffIndex);
#endif

			if (wordLength <= charsAvailable) {
				strncpy(buff + buffIndex, str + startWord, wordLength);
				charsAvailable -= wordLength;
				buffIndex += wordLength;
			} else if (wordLength <= charsPerLine) {
				while (charsAvailable > 0) {
					buff[buffIndex++] = ' ';
					charsAvailable--;
				}

				charsAvailable = charsPerLine;
				strncpy(buff + buffIndex, str + startWord, wordLength);
				buffIndex += wordLength;
				charsAvailable -= wordLength;
			} else {
				strncpy(buff + buffIndex, str + startWord, wordLength);
				buffIndex += wordLength;
				charsAvailable -= wordLength;
				while (charsAvailable <= 0) {
					charsAvailable = charsPerLine;
				}
			}

			if (charsAvailable > 0 && str[i] != '\0') {
				buff[buffIndex++] = ' ';
				charsAvailable--;
			} else {
				charsAvailable = charsPerLine;
			}
		}
	}

	buff[buffIndex] = '\0';

#if DEBUG > 1
	printf("Debug: copy wrapped text to label\n");
	printf("New text: %s\n", buff);
#endif
	componentSetText(component, buff);
#if DEBUG > 1
	printf("Debug: text copied\n");
#endif
}

void labelSetBackgroundColor(COMPONENT* component, int rgb) {
	LABEL *label = (LABEL*) component;

	label->backgroundColor = rgb;
}

int labelGetBackgroundColor(COMPONENT* component) {
	LABEL *label = (LABEL*) component;

	return label->backgroundColor;
}

void labelSetBorderColor(COMPONENT* component, int rgb) {
	LABEL *label = (LABEL*) component;

	label->borderColor = rgb;
}

int labelGetBorderColor(COMPONENT* component) {
	LABEL *label = (LABEL*) component;

	return label->borderColor;
}
