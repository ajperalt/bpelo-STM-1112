/*
 * guiComponents.h
 *
 *  Created on: May 5, 2011
 *      Author: philip
 */

#ifndef GUICOMPONENTS_H_
#define GUICOMPONENTS_H_

/**
 * \file component.h
 *
 * \brief Has some functions
 */

#include "../structs.h"

/**
 * \brief Solve the color.
 *
 * It is possible color has for example the color \a GUI_USE_DEFAULT_FOREGROUND_COLOR . This needs to be translated to an actual color.
 * This function will do this. If color is a special color, it gets solved, otherwise it just return the color.
 *
 * @param color The color that needs to be solved
 * @return If the color is a special color, it gets translated. Otherwise \a color is returned as it is a normal color
 */
int solveColor(int color);

/**
 * \brief Solve the font.
 *
 * It is possible font has for example the font \a GUI_USE_DEFAULT_FONT . This needs to be translated to an actual font.
 * This function will do this. If font is a special font, it gets solved, otherwise it just return the font.
 *
 * @param font The font that needs to be solved
 * @return If the font is a special font, it gets translated. Otherwise \a font is returned as it is a normal font
 */
char solveFont(char font);

/**
 * \brief Calculate the size of the component
 *
 * In fact, this function will just delegate the component to the right calculateSize function (like buttonCalculateSize).
 *
 * @param component The component of which you want to calculate the size
 * @param width Here we will store the width
 * @param height Here we will store the height
 */
void componentCalculateSize(BASE_COMPONENT* component, short* width, short* height);

// some features components can have
#define GUI_STANDARD_COMPONENT	0x00
#define	GUI_HAS_TEXT			0x01
#define GUI_HAS_FLOAT_VALUE		0x02
#define GUI_HAS_FOREGROUND		0x04
#define GUI_HAS_BACKGROUND		0x08
#define GUI_HAS_LIMITS			0x016

// 2 byte identifier:
// 8 MSB's: identifies the type of component
// 8 LSB's: identifies the features it has
#define GUI_CIRCLE				((0x00 << 8) | GUI_STANDARD_COMPONENT)
#define	GUI_RECTANGLE			((0x01 << 8) | GUI_STANDARD_COMPONENT)
#define GUI_OVAL				((0x02 << 8) | GUI_STANDARD_COMPONENT)
#define GUI_ROUNDRECT			((0x03 << 8) | GUI_STANDARD_COMPONENT)
#define	GUI_LABEL				((0x04 << 8) | GUI_HAS_TEXT | GUI_HAS_FOREGROUND)
#define GUI_BUTTON				((0x05 << 8) | GUI_HAS_TEXT | GUI_HAS_FOREGROUND | GUI_HAS_BACKGROUND)
#define GUI_SPINNER				((0x06 << 8) | GUI_HAS_FLOAT_VALUE | GUI_HAS_FOREGROUND | GUI_HAS_BACKGROUND | GUI_HAS_LIMITS)

#endif /* GUICOMPONENTS_H_ */
